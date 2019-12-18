#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct msghdr {int /*<<< orphan*/  msg_flags; } ;
struct hash_ctx {int result; int /*<<< orphan*/  wait; int /*<<< orphan*/  req; scalar_t__ more; } ;
struct alg_sock {struct hash_ctx* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_TRUNC ; 
 int /*<<< orphan*/  ahash_request_set_crypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct alg_sock* alg_sk (struct sock*) ; 
 unsigned int crypto_ahash_digestsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_ahash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (int /*<<< orphan*/ *) ; 
 int crypto_wait_req (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hash_alloc_result (struct sock*,struct hash_ctx*) ; 
 int /*<<< orphan*/  hash_free_result (struct sock*,struct hash_ctx*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int memcpy_to_msg (struct msghdr*,int,size_t) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int hash_recvmsg(struct socket *sock, struct msghdr *msg, size_t len,
			int flags)
{
	struct sock *sk = sock->sk;
	struct alg_sock *ask = alg_sk(sk);
	struct hash_ctx *ctx = ask->private;
	unsigned ds = crypto_ahash_digestsize(crypto_ahash_reqtfm(&ctx->req));
	bool result;
	int err;

	if (len > ds)
		len = ds;
	else if (len < ds)
		msg->msg_flags |= MSG_TRUNC;

	lock_sock(sk);
	result = ctx->result;
	err = hash_alloc_result(sk, ctx);
	if (err)
		goto unlock;

	ahash_request_set_crypt(&ctx->req, NULL, ctx->result, 0);

	if (!result && !ctx->more) {
		err = crypto_wait_req(crypto_ahash_init(&ctx->req),
				      &ctx->wait);
		if (err)
			goto unlock;
	}

	if (!result || ctx->more) {
		ctx->more = 0;
		err = crypto_wait_req(crypto_ahash_final(&ctx->req),
				      &ctx->wait);
		if (err)
			goto unlock;
	}

	err = memcpy_to_msg(msg, ctx->result, len);

unlock:
	hash_free_result(sk, ctx);
	release_sock(sk);

	return err ?: len;
}