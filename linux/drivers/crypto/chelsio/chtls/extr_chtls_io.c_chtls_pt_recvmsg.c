#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct tcp_sock {int urg_data; scalar_t__ urg_seq; scalar_t__ copied_seq; } ;
struct TYPE_3__ {scalar_t__ tail; } ;
struct sock {scalar_t__ sk_state; int sk_shutdown; int /*<<< orphan*/  sk_receive_queue; TYPE_1__ sk_backlog; scalar_t__ sk_err; int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;} ;
struct sk_buff {unsigned long len; int /*<<< orphan*/  hdr_len; } ;
struct msghdr {int dummy; } ;
struct chtls_hws {unsigned long copied_seq; int /*<<< orphan*/  rcvpld; } ;
struct chtls_sock {scalar_t__ wr_credits; scalar_t__ wr_max_credits; int /*<<< orphan*/  txq; struct chtls_hws tlshws; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSK_UPDATE_RCV_WND ; 
 int EAGAIN ; 
 int EFAULT ; 
 int ENOTCONN ; 
 int MSG_WAITALL ; 
 int RCV_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  SOCK_URGINLINE ; 
 scalar_t__ TCP_CLOSE ; 
 int ULPCB_FLAG_TLS_HDR ; 
 TYPE_2__* ULP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  chtls_cleanup_rbuf (struct sock*,int) ; 
 int /*<<< orphan*/  chtls_free_skb (struct sock*,struct sk_buff*) ; 
 scalar_t__ chtls_push_frames (struct chtls_sock*,int) ; 
 int csk_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_wait_data (struct sock*,long*,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_copy_datagram_msg (struct sk_buff*,unsigned long,struct msghdr*,unsigned long) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int sock_error (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int sock_intr_errno (long) ; 
 int sock_rcvlowat (struct sock*,int,size_t) ; 
 long sock_rcvtimeo (struct sock*,int) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int chtls_pt_recvmsg(struct sock *sk, struct msghdr *msg, size_t len,
			    int nonblock, int flags, int *addr_len)
{
	struct chtls_sock *csk = rcu_dereference_sk_user_data(sk);
	struct chtls_hws *hws = &csk->tlshws;
	struct tcp_sock *tp = tcp_sk(sk);
	unsigned long avail;
	int buffers_freed;
	int copied = 0;
	int target;
	long timeo;

	buffers_freed = 0;

	timeo = sock_rcvtimeo(sk, nonblock);
	target = sock_rcvlowat(sk, flags & MSG_WAITALL, len);

	if (unlikely(csk_flag(sk, CSK_UPDATE_RCV_WND)))
		chtls_cleanup_rbuf(sk, copied);

	do {
		struct sk_buff *skb;
		u32 offset = 0;

		if (unlikely(tp->urg_data &&
			     tp->urg_seq == tp->copied_seq)) {
			if (copied)
				break;
			if (signal_pending(current)) {
				copied = timeo ? sock_intr_errno(timeo) :
					-EAGAIN;
				break;
			}
		}
		skb = skb_peek(&sk->sk_receive_queue);
		if (skb)
			goto found_ok_skb;
		if (csk->wr_credits &&
		    skb_queue_len(&csk->txq) &&
		    chtls_push_frames(csk, csk->wr_credits ==
				      csk->wr_max_credits))
			sk->sk_write_space(sk);

		if (copied >= target && !sk->sk_backlog.tail)
			break;

		if (copied) {
			if (sk->sk_err || sk->sk_state == TCP_CLOSE ||
			    (sk->sk_shutdown & RCV_SHUTDOWN) ||
			    signal_pending(current))
				break;

			if (!timeo)
				break;
		} else {
			if (sock_flag(sk, SOCK_DONE))
				break;
			if (sk->sk_err) {
				copied = sock_error(sk);
				break;
			}
			if (sk->sk_shutdown & RCV_SHUTDOWN)
				break;
			if (sk->sk_state == TCP_CLOSE) {
				copied = -ENOTCONN;
				break;
			}
			if (!timeo) {
				copied = -EAGAIN;
				break;
			}
			if (signal_pending(current)) {
				copied = sock_intr_errno(timeo);
				break;
			}
		}
		if (sk->sk_backlog.tail) {
			release_sock(sk);
			lock_sock(sk);
			chtls_cleanup_rbuf(sk, copied);
			continue;
		}

		if (copied >= target)
			break;
		chtls_cleanup_rbuf(sk, copied);
		sk_wait_data(sk, &timeo, NULL);
		continue;
found_ok_skb:
		if (!skb->len) {
			skb_dst_set(skb, NULL);
			__skb_unlink(skb, &sk->sk_receive_queue);
			kfree_skb(skb);

			if (!copied && !timeo) {
				copied = -EAGAIN;
				break;
			}

			if (copied < target) {
				release_sock(sk);
				lock_sock(sk);
				continue;
			}
			break;
		}
		offset = hws->copied_seq;
		avail = skb->len - offset;
		if (len < avail)
			avail = len;

		if (unlikely(tp->urg_data)) {
			u32 urg_offset = tp->urg_seq - tp->copied_seq;

			if (urg_offset < avail) {
				if (urg_offset) {
					avail = urg_offset;
				} else if (!sock_flag(sk, SOCK_URGINLINE)) {
					/* First byte is urgent, skip */
					tp->copied_seq++;
					offset++;
					avail--;
					if (!avail)
						goto skip_copy;
				}
			}
		}
		if (skb_copy_datagram_msg(skb, offset, msg, avail)) {
			if (!copied) {
				copied = -EFAULT;
				break;
			}
		}

		copied += avail;
		len -= avail;
		hws->copied_seq += avail;
skip_copy:
		if (tp->urg_data && after(tp->copied_seq, tp->urg_seq))
			tp->urg_data = 0;

		if ((avail + offset) >= skb->len) {
			if (ULP_SKB_CB(skb)->flags & ULPCB_FLAG_TLS_HDR) {
				tp->copied_seq += skb->len;
				hws->rcvpld = skb->hdr_len;
			} else {
				tp->copied_seq += hws->rcvpld;
			}
			chtls_free_skb(sk, skb);
			buffers_freed++;
			hws->copied_seq = 0;
			if (copied >= target &&
			    !skb_peek(&sk->sk_receive_queue))
				break;
		}
	} while (len > 0);

	if (buffers_freed)
		chtls_cleanup_rbuf(sk, copied);
	release_sock(sk);
	return copied;
}