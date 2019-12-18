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
struct sshkey {int dummy; } ;
struct sshbuf {int dummy; } ;
struct fuzz {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_EQ (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_PTR_NE (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int FUZZ_1_BIT_FLIP ; 
 int FUZZ_1_BYTE_FLIP ; 
 int FUZZ_TRUNCATE_END ; 
 int FUZZ_TRUNCATE_START ; 
 int /*<<< orphan*/  TEST_ONERROR (int /*<<< orphan*/ ,struct fuzz*) ; 
 struct fuzz* fuzz_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuzz_cleanup (struct fuzz*) ; 
 int /*<<< orphan*/  fuzz_done (struct fuzz*) ; 
 int /*<<< orphan*/  fuzz_len (struct fuzz*) ; 
 int /*<<< orphan*/  fuzz_next (struct fuzz*) ; 
 int /*<<< orphan*/  fuzz_ptr (struct fuzz*) ; 
 int /*<<< orphan*/  onerror ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_mutable_ptr (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int /*<<< orphan*/  sshbuf_ptr (struct sshbuf*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 scalar_t__ sshkey_from_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sshkey**) ; 
 scalar_t__ sshkey_putb (struct sshkey*,struct sshbuf*) ; 

__attribute__((used)) static void
public_fuzz(struct sshkey *k)
{
	struct sshkey *k1;
	struct sshbuf *buf;
	struct fuzz *fuzz;

	ASSERT_PTR_NE(buf = sshbuf_new(), NULL);
	ASSERT_INT_EQ(sshkey_putb(k, buf), 0);
	/* XXX need a way to run the tests in "slow, but complete" mode */
	fuzz = fuzz_begin(FUZZ_1_BIT_FLIP | /* XXX too slow FUZZ_2_BIT_FLIP | */
	    FUZZ_1_BYTE_FLIP | /* XXX too slow FUZZ_2_BYTE_FLIP | */
	    FUZZ_TRUNCATE_START | FUZZ_TRUNCATE_END,
	    sshbuf_mutable_ptr(buf), sshbuf_len(buf));
	ASSERT_INT_EQ(sshkey_from_blob(sshbuf_ptr(buf), sshbuf_len(buf),
	    &k1), 0);
	sshkey_free(k1);
	sshbuf_free(buf);
	TEST_ONERROR(onerror, fuzz);
	for(; !fuzz_done(fuzz); fuzz_next(fuzz)) {
		if (sshkey_from_blob(fuzz_ptr(fuzz), fuzz_len(fuzz), &k1) == 0)
			sshkey_free(k1);
	}
	fuzz_cleanup(fuzz);
}