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
typedef  int u_char ;
struct sshkey {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_INT_NE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_PTR_NE (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASSERT_SIZE_T_GT (size_t,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  sshkey_sign (struct sshkey*,int**,size_t*,int const*,size_t,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshkey_verify (struct sshkey*,int*,size_t,int const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
signature_test(struct sshkey *k, struct sshkey *bad, const char *sig_alg,
    const u_char *d, size_t l)
{
	size_t len;
	u_char *sig;

	ASSERT_INT_EQ(sshkey_sign(k, &sig, &len, d, l, sig_alg, 0), 0);
	ASSERT_SIZE_T_GT(len, 8);
	ASSERT_PTR_NE(sig, NULL);
	ASSERT_INT_EQ(sshkey_verify(k, sig, len, d, l, NULL, 0), 0);
	ASSERT_INT_NE(sshkey_verify(bad, sig, len, d, l, NULL, 0), 0);
	/* Fuzz test is more comprehensive, this is just a smoke test */
	sig[len - 5] ^= 0x10;
	ASSERT_INT_NE(sshkey_verify(k, sig, len, d, l, NULL, 0), 0);
	free(sig);
}