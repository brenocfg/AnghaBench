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
typedef  int /*<<< orphan*/  u8 ;
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct rng_ctx {int /*<<< orphan*/  drng; } ;
struct msghdr {int dummy; } ;
struct alg_sock {struct rng_ctx* private; } ;

/* Variables and functions */
 int EFAULT ; 
 int MAXSIZE ; 
 struct alg_sock* alg_sk (struct sock*) ; 
 int crypto_rng_get_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int memcpy_to_msg (struct msghdr*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memzero_explicit (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int rng_recvmsg(struct socket *sock, struct msghdr *msg, size_t len,
		       int flags)
{
	struct sock *sk = sock->sk;
	struct alg_sock *ask = alg_sk(sk);
	struct rng_ctx *ctx = ask->private;
	int err = -EFAULT;
	int genlen = 0;
	u8 result[MAXSIZE];

	if (len == 0)
		return 0;
	if (len > MAXSIZE)
		len = MAXSIZE;

	/*
	 * although not strictly needed, this is a precaution against coding
	 * errors
	 */
	memset(result, 0, len);

	/*
	 * The enforcement of a proper seeding of an RNG is done within an
	 * RNG implementation. Some RNGs (DRBG, krng) do not need specific
	 * seeding as they automatically seed. The X9.31 DRNG will return
	 * an error if it was not seeded properly.
	 */
	genlen = crypto_rng_get_bytes(ctx->drng, result, len);
	if (genlen < 0)
		return genlen;

	err = memcpy_to_msg(msg, result, len);
	memzero_explicit(result, len);

	return err ? err : len;
}