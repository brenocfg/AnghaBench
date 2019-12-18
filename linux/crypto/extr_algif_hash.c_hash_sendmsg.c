#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sock {int sk_sndbuf; } ;
struct msghdr {int msg_flags; int /*<<< orphan*/  msg_iter; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sg; } ;
struct hash_ctx {int more; int /*<<< orphan*/  wait; int /*<<< orphan*/  req; int /*<<< orphan*/ * result; TYPE_1__ sgl; } ;
struct alg_sock {struct hash_ctx* private; } ;

/* Variables and functions */
 int ALG_MAX_PAGES ; 
 int MSG_MORE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  af_alg_free_sg (TYPE_1__*) ; 
 int af_alg_make_sg (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct alg_sock* alg_sk (struct sock*) ; 
 int /*<<< orphan*/  crypto_ahash_final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_ahash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_ahash_update (int /*<<< orphan*/ *) ; 
 int crypto_wait_req (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hash_alloc_result (struct sock*,struct hash_ctx*) ; 
 int /*<<< orphan*/  hash_free_result (struct sock*,struct hash_ctx*) ; 
 int /*<<< orphan*/  iov_iter_advance (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int msg_data_left (struct msghdr*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int hash_sendmsg(struct socket *sock, struct msghdr *msg,
			size_t ignored)
{
	int limit = ALG_MAX_PAGES * PAGE_SIZE;
	struct sock *sk = sock->sk;
	struct alg_sock *ask = alg_sk(sk);
	struct hash_ctx *ctx = ask->private;
	long copied = 0;
	int err;

	if (limit > sk->sk_sndbuf)
		limit = sk->sk_sndbuf;

	lock_sock(sk);
	if (!ctx->more) {
		if ((msg->msg_flags & MSG_MORE))
			hash_free_result(sk, ctx);

		err = crypto_wait_req(crypto_ahash_init(&ctx->req), &ctx->wait);
		if (err)
			goto unlock;
	}

	ctx->more = 0;

	while (msg_data_left(msg)) {
		int len = msg_data_left(msg);

		if (len > limit)
			len = limit;

		len = af_alg_make_sg(&ctx->sgl, &msg->msg_iter, len);
		if (len < 0) {
			err = copied ? 0 : len;
			goto unlock;
		}

		ahash_request_set_crypt(&ctx->req, ctx->sgl.sg, NULL, len);

		err = crypto_wait_req(crypto_ahash_update(&ctx->req),
				      &ctx->wait);
		af_alg_free_sg(&ctx->sgl);
		if (err)
			goto unlock;

		copied += len;
		iov_iter_advance(&msg->msg_iter, len);
	}

	err = 0;

	ctx->more = msg->msg_flags & MSG_MORE;
	if (!ctx->more) {
		err = hash_alloc_result(sk, ctx);
		if (err)
			goto unlock;

		ahash_request_set_crypt(&ctx->req, NULL, ctx->result, 0);
		err = crypto_wait_req(crypto_ahash_final(&ctx->req),
				      &ctx->wait);
	}

unlock:
	release_sock(sk);

	return err ?: copied;
}