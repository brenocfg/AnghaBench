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
typedef  char u_char ;
struct sshkey {int dummy; } ;
struct fuzz {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_INT_NE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_SIZE_T_GT (size_t,int /*<<< orphan*/ ) ; 
 int FUZZ_1_BIT_FLIP ; 
 int FUZZ_1_BYTE_FLIP ; 
 int FUZZ_2_BYTE_FLIP ; 
 int FUZZ_TRUNCATE_END ; 
 int FUZZ_TRUNCATE_START ; 
 int /*<<< orphan*/  TEST_ONERROR (int /*<<< orphan*/ ,struct fuzz*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct fuzz* fuzz_begin (int,char*,size_t) ; 
 int /*<<< orphan*/  fuzz_cleanup (struct fuzz*) ; 
 int /*<<< orphan*/  fuzz_done (struct fuzz*) ; 
 size_t fuzz_len (struct fuzz*) ; 
 scalar_t__ fuzz_matches_original (struct fuzz*) ; 
 int /*<<< orphan*/  fuzz_next (struct fuzz*) ; 
 char* fuzz_ptr (struct fuzz*) ; 
 int /*<<< orphan*/  onerror ; 
 int /*<<< orphan*/  sshkey_sign (struct sshkey*,char**,size_t*,char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshkey_verify (struct sshkey*,char*,size_t,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sig_fuzz(struct sshkey *k, const char *sig_alg)
{
	struct fuzz *fuzz;
	u_char *sig, c[] = "some junk to be signed";
	size_t l;

	ASSERT_INT_EQ(sshkey_sign(k, &sig, &l, c, sizeof(c), sig_alg, 0), 0);
	ASSERT_SIZE_T_GT(l, 0);
	fuzz = fuzz_begin(FUZZ_1_BIT_FLIP | /* too slow FUZZ_2_BIT_FLIP | */
	    FUZZ_1_BYTE_FLIP | FUZZ_2_BYTE_FLIP |
	    FUZZ_TRUNCATE_START | FUZZ_TRUNCATE_END, sig, l);
	ASSERT_INT_EQ(sshkey_verify(k, sig, l, c, sizeof(c), NULL, 0), 0);
	free(sig);
	TEST_ONERROR(onerror, fuzz);
	for(; !fuzz_done(fuzz); fuzz_next(fuzz)) {
		/* Ensure 1-bit difference at least */
		if (fuzz_matches_original(fuzz))
			continue;
		ASSERT_INT_NE(sshkey_verify(k, fuzz_ptr(fuzz), fuzz_len(fuzz),
		    c, sizeof(c), NULL, 0), 0);
	}
	fuzz_cleanup(fuzz);
}