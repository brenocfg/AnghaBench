#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcp_sock {int write_seq; } ;
struct sock {int sk_wmem_queued; TYPE_1__* sk_socket; } ;
struct sk_buff {int len; int data_len; int truesize; } ;
struct page {int dummy; } ;
struct chtls_sock {int mss; int /*<<< orphan*/  txq; struct chtls_dev* cdev; } ;
struct chtls_dev {int dummy; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSK_TX_MORE_DATA ; 
 int MAX_SKB_FRAGS ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int TCPF_CLOSE_WAIT ; 
 int TCPF_ESTABLISHED ; 
 int /*<<< orphan*/  TX_TLSHDR_LEN ; 
 int ULPCB_FLAG_NO_APPEND ; 
 TYPE_3__* ULP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  chtls_tcp_push (struct sock*,int) ; 
 scalar_t__ corked (struct tcp_sock*,int) ; 
 scalar_t__ csk_conn_inline (struct chtls_sock*) ; 
 int /*<<< orphan*/  csk_mem_free (struct chtls_dev*,struct sock*) ; 
 int /*<<< orphan*/  csk_reset_flag (struct chtls_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csk_set_flag (struct chtls_sock*,int /*<<< orphan*/ ) ; 
 int csk_wait_memory (struct chtls_dev*,struct sock*,long*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct sk_buff* get_record_skb (struct sock*,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* get_tx_skb (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_tls_tx (struct chtls_sock*) ; 
 int /*<<< orphan*/  push_frames_if_head (struct sock*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  select_size (struct sock*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_in_state (struct sock*,int) ; 
 int sk_stream_error (struct sock*,int,int) ; 
 scalar_t__ sk_stream_min_wspace (struct sock*) ; 
 int sk_stream_wait_connect (struct sock*,long*) ; 
 scalar_t__ sk_stream_wspace (struct sock*) ; 
 scalar_t__ skb_can_coalesce (struct sk_buff*,int,struct page*,int) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int,struct page*,int,int) ; 
 int /*<<< orphan*/  skb_frag_size_add (int /*<<< orphan*/ *,int) ; 
 struct sk_buff* skb_peek_tail (int /*<<< orphan*/ *) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 long sock_sndtimeo (struct sock*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tx_skb_finalize (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int chtls_sendpage(struct sock *sk, struct page *page,
		   int offset, size_t size, int flags)
{
	struct chtls_sock *csk;
	struct chtls_dev *cdev;
	int mss, err, copied;
	struct tcp_sock *tp;
	long timeo;

	tp = tcp_sk(sk);
	copied = 0;
	csk = rcu_dereference_sk_user_data(sk);
	cdev = csk->cdev;
	timeo = sock_sndtimeo(sk, flags & MSG_DONTWAIT);

	err = sk_stream_wait_connect(sk, &timeo);
	if (!sk_in_state(sk, TCPF_ESTABLISHED | TCPF_CLOSE_WAIT) &&
	    err != 0)
		goto out_err;

	mss = csk->mss;
	csk_set_flag(csk, CSK_TX_MORE_DATA);

	while (size > 0) {
		struct sk_buff *skb = skb_peek_tail(&csk->txq);
		int copy, i;

		if (!skb || (ULP_SKB_CB(skb)->flags & ULPCB_FLAG_NO_APPEND) ||
		    (copy = mss - skb->len) <= 0) {
new_buf:
			if (!csk_mem_free(cdev, sk))
				goto wait_for_sndbuf;

			if (is_tls_tx(csk)) {
				skb = get_record_skb(sk,
						     select_size(sk, size,
								 flags,
								 TX_TLSHDR_LEN),
						     true);
			} else {
				skb = get_tx_skb(sk, 0);
			}
			if (!skb)
				goto wait_for_memory;
			copy = mss;
		}
		if (copy > size)
			copy = size;

		i = skb_shinfo(skb)->nr_frags;
		if (skb_can_coalesce(skb, i, page, offset)) {
			skb_frag_size_add(&skb_shinfo(skb)->frags[i - 1], copy);
		} else if (i < MAX_SKB_FRAGS) {
			get_page(page);
			skb_fill_page_desc(skb, i, page, offset, copy);
		} else {
			tx_skb_finalize(skb);
			push_frames_if_head(sk);
			goto new_buf;
		}

		skb->len += copy;
		if (skb->len == mss)
			tx_skb_finalize(skb);
		skb->data_len += copy;
		skb->truesize += copy;
		sk->sk_wmem_queued += copy;
		tp->write_seq += copy;
		copied += copy;
		offset += copy;
		size -= copy;

		if (corked(tp, flags) &&
		    (sk_stream_wspace(sk) < sk_stream_min_wspace(sk)))
			ULP_SKB_CB(skb)->flags |= ULPCB_FLAG_NO_APPEND;

		if (!size)
			break;

		if (unlikely(ULP_SKB_CB(skb)->flags & ULPCB_FLAG_NO_APPEND))
			push_frames_if_head(sk);
		continue;
wait_for_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
wait_for_memory:
		err = csk_wait_memory(cdev, sk, &timeo);
		if (err)
			goto do_error;
	}
out:
	csk_reset_flag(csk, CSK_TX_MORE_DATA);
	if (copied)
		chtls_tcp_push(sk, flags);
done:
	release_sock(sk);
	return copied;

do_error:
	if (copied)
		goto out;

out_err:
	if (csk_conn_inline(csk))
		csk_reset_flag(csk, CSK_TX_MORE_DATA);
	copied = sk_stream_error(sk, flags, err);
	goto done;
}