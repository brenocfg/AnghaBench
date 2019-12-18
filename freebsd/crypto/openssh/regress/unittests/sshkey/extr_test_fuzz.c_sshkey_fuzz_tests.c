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
 int /*<<< orphan*/  FUZZ_BASE64 ; 
 int /*<<< orphan*/  TEST_DONE () ; 
 int /*<<< orphan*/  TEST_ONERROR (int /*<<< orphan*/ ,struct fuzz*) ; 
 int /*<<< orphan*/  TEST_START (char*) ; 
 struct fuzz* fuzz_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuzz_cleanup (struct fuzz*) ; 
 int /*<<< orphan*/  fuzz_done (struct fuzz*) ; 
 int /*<<< orphan*/  fuzz_len (struct fuzz*) ; 
 int /*<<< orphan*/  fuzz_next (struct fuzz*) ; 
 int /*<<< orphan*/  fuzz_ptr (struct fuzz*) ; 
 struct sshbuf* load_file (char*) ; 
 int /*<<< orphan*/  onerror ; 
 int /*<<< orphan*/  public_fuzz (struct sshkey*) ; 
 int /*<<< orphan*/  sig_fuzz (struct sshkey*,char*) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_mutable_ptr (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int sshbuf_put (struct sshbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_reset (struct sshbuf*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 scalar_t__ sshkey_load_cert (int /*<<< orphan*/ ,struct sshkey**) ; 
 scalar_t__ sshkey_parse_private_fileblob (struct sshbuf*,char*,struct sshkey**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_data_file (char*) ; 

void
sshkey_fuzz_tests(void)
{
	struct sshkey *k1;
	struct sshbuf *buf, *fuzzed;
	struct fuzz *fuzz;
	int r;


	TEST_START("fuzz RSA private");
	buf = load_file("rsa_1");
	fuzz = fuzz_begin(FUZZ_BASE64, sshbuf_mutable_ptr(buf),
	    sshbuf_len(buf));
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshkey_free(k1);
	sshbuf_free(buf);
	ASSERT_PTR_NE(fuzzed = sshbuf_new(), NULL);
	TEST_ONERROR(onerror, fuzz);
	for(; !fuzz_done(fuzz); fuzz_next(fuzz)) {
		r = sshbuf_put(fuzzed, fuzz_ptr(fuzz), fuzz_len(fuzz));
		ASSERT_INT_EQ(r, 0);
		if (sshkey_parse_private_fileblob(fuzzed, "", &k1, NULL) == 0)
			sshkey_free(k1);
		sshbuf_reset(fuzzed);
	}
	sshbuf_free(fuzzed);
	fuzz_cleanup(fuzz);
	TEST_DONE();

	TEST_START("fuzz RSA new-format private");
	buf = load_file("rsa_n");
	fuzz = fuzz_begin(FUZZ_BASE64, sshbuf_mutable_ptr(buf),
	    sshbuf_len(buf));
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshkey_free(k1);
	sshbuf_free(buf);
	ASSERT_PTR_NE(fuzzed = sshbuf_new(), NULL);
	TEST_ONERROR(onerror, fuzz);
	for(; !fuzz_done(fuzz); fuzz_next(fuzz)) {
		r = sshbuf_put(fuzzed, fuzz_ptr(fuzz), fuzz_len(fuzz));
		ASSERT_INT_EQ(r, 0);
		if (sshkey_parse_private_fileblob(fuzzed, "", &k1, NULL) == 0)
			sshkey_free(k1);
		sshbuf_reset(fuzzed);
	}
	sshbuf_free(fuzzed);
	fuzz_cleanup(fuzz);
	TEST_DONE();

	TEST_START("fuzz DSA private");
	buf = load_file("dsa_1");
	fuzz = fuzz_begin(FUZZ_BASE64, sshbuf_mutable_ptr(buf),
	    sshbuf_len(buf));
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshkey_free(k1);
	sshbuf_free(buf);
	ASSERT_PTR_NE(fuzzed = sshbuf_new(), NULL);
	TEST_ONERROR(onerror, fuzz);
	for(; !fuzz_done(fuzz); fuzz_next(fuzz)) {
		r = sshbuf_put(fuzzed, fuzz_ptr(fuzz), fuzz_len(fuzz));
		ASSERT_INT_EQ(r, 0);
		if (sshkey_parse_private_fileblob(fuzzed, "", &k1, NULL) == 0)
			sshkey_free(k1);
		sshbuf_reset(fuzzed);
	}
	sshbuf_free(fuzzed);
	fuzz_cleanup(fuzz);
	TEST_DONE();

	TEST_START("fuzz DSA new-format private");
	buf = load_file("dsa_n");
	fuzz = fuzz_begin(FUZZ_BASE64, sshbuf_mutable_ptr(buf),
	    sshbuf_len(buf));
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshkey_free(k1);
	sshbuf_free(buf);
	ASSERT_PTR_NE(fuzzed = sshbuf_new(), NULL);
	TEST_ONERROR(onerror, fuzz);
	for(; !fuzz_done(fuzz); fuzz_next(fuzz)) {
		r = sshbuf_put(fuzzed, fuzz_ptr(fuzz), fuzz_len(fuzz));
		ASSERT_INT_EQ(r, 0);
		if (sshkey_parse_private_fileblob(fuzzed, "", &k1, NULL) == 0)
			sshkey_free(k1);
		sshbuf_reset(fuzzed);
	}
	sshbuf_free(fuzzed);
	fuzz_cleanup(fuzz);
	TEST_DONE();

#ifdef OPENSSL_HAS_ECC
	TEST_START("fuzz ECDSA private");
	buf = load_file("ecdsa_1");
	fuzz = fuzz_begin(FUZZ_BASE64, sshbuf_mutable_ptr(buf),
	    sshbuf_len(buf));
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshkey_free(k1);
	sshbuf_free(buf);
	ASSERT_PTR_NE(fuzzed = sshbuf_new(), NULL);
	TEST_ONERROR(onerror, fuzz);
	for(; !fuzz_done(fuzz); fuzz_next(fuzz)) {
		r = sshbuf_put(fuzzed, fuzz_ptr(fuzz), fuzz_len(fuzz));
		ASSERT_INT_EQ(r, 0);
		if (sshkey_parse_private_fileblob(fuzzed, "", &k1, NULL) == 0)
			sshkey_free(k1);
		sshbuf_reset(fuzzed);
	}
	sshbuf_free(fuzzed);
	fuzz_cleanup(fuzz);
	TEST_DONE();

	TEST_START("fuzz ECDSA new-format private");
	buf = load_file("ecdsa_n");
	fuzz = fuzz_begin(FUZZ_BASE64, sshbuf_mutable_ptr(buf),
	    sshbuf_len(buf));
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshkey_free(k1);
	sshbuf_free(buf);
	ASSERT_PTR_NE(fuzzed = sshbuf_new(), NULL);
	TEST_ONERROR(onerror, fuzz);
	for(; !fuzz_done(fuzz); fuzz_next(fuzz)) {
		r = sshbuf_put(fuzzed, fuzz_ptr(fuzz), fuzz_len(fuzz));
		ASSERT_INT_EQ(r, 0);
		if (sshkey_parse_private_fileblob(fuzzed, "", &k1, NULL) == 0)
			sshkey_free(k1);
		sshbuf_reset(fuzzed);
	}
	sshbuf_free(fuzzed);
	fuzz_cleanup(fuzz);
	TEST_DONE();
#endif

	TEST_START("fuzz Ed25519 private");
	buf = load_file("ed25519_1");
	fuzz = fuzz_begin(FUZZ_BASE64, sshbuf_mutable_ptr(buf),
	    sshbuf_len(buf));
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshkey_free(k1);
	sshbuf_free(buf);
	ASSERT_PTR_NE(fuzzed = sshbuf_new(), NULL);
	TEST_ONERROR(onerror, fuzz);
	for(; !fuzz_done(fuzz); fuzz_next(fuzz)) {
		r = sshbuf_put(fuzzed, fuzz_ptr(fuzz), fuzz_len(fuzz));
		ASSERT_INT_EQ(r, 0);
		if (sshkey_parse_private_fileblob(fuzzed, "", &k1, NULL) == 0)
			sshkey_free(k1);
		sshbuf_reset(fuzzed);
	}
	sshbuf_free(fuzzed);
	fuzz_cleanup(fuzz);
	TEST_DONE();

	TEST_START("fuzz RSA public");
	buf = load_file("rsa_1");
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshbuf_free(buf);
	public_fuzz(k1);
	sshkey_free(k1);
	TEST_DONE();

	TEST_START("fuzz RSA cert");
	ASSERT_INT_EQ(sshkey_load_cert(test_data_file("rsa_1"), &k1), 0);
	public_fuzz(k1);
	sshkey_free(k1);
	TEST_DONE();

	TEST_START("fuzz DSA public");
	buf = load_file("dsa_1");
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshbuf_free(buf);
	public_fuzz(k1);
	sshkey_free(k1);
	TEST_DONE();

	TEST_START("fuzz DSA cert");
	ASSERT_INT_EQ(sshkey_load_cert(test_data_file("dsa_1"), &k1), 0);
	public_fuzz(k1);
	sshkey_free(k1);
	TEST_DONE();

#ifdef OPENSSL_HAS_ECC
	TEST_START("fuzz ECDSA public");
	buf = load_file("ecdsa_1");
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshbuf_free(buf);
	public_fuzz(k1);
	sshkey_free(k1);
	TEST_DONE();

	TEST_START("fuzz ECDSA cert");
	ASSERT_INT_EQ(sshkey_load_cert(test_data_file("ecdsa_1"), &k1), 0);
	public_fuzz(k1);
	sshkey_free(k1);
	TEST_DONE();
#endif

	TEST_START("fuzz Ed25519 public");
	buf = load_file("ed25519_1");
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshbuf_free(buf);
	public_fuzz(k1);
	sshkey_free(k1);
	TEST_DONE();

	TEST_START("fuzz Ed25519 cert");
	ASSERT_INT_EQ(sshkey_load_cert(test_data_file("ed25519_1"), &k1), 0);
	public_fuzz(k1);
	sshkey_free(k1);
	TEST_DONE();

	TEST_START("fuzz RSA sig");
	buf = load_file("rsa_1");
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshbuf_free(buf);
	sig_fuzz(k1, "ssh-rsa");
	sshkey_free(k1);
	TEST_DONE();

	TEST_START("fuzz RSA SHA256 sig");
	buf = load_file("rsa_1");
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshbuf_free(buf);
	sig_fuzz(k1, "rsa-sha2-256");
	sshkey_free(k1);
	TEST_DONE();

	TEST_START("fuzz RSA SHA512 sig");
	buf = load_file("rsa_1");
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshbuf_free(buf);
	sig_fuzz(k1, "rsa-sha2-512");
	sshkey_free(k1);
	TEST_DONE();

	TEST_START("fuzz DSA sig");
	buf = load_file("dsa_1");
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshbuf_free(buf);
	sig_fuzz(k1, NULL);
	sshkey_free(k1);
	TEST_DONE();

#ifdef OPENSSL_HAS_ECC
	TEST_START("fuzz ECDSA sig");
	buf = load_file("ecdsa_1");
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshbuf_free(buf);
	sig_fuzz(k1, NULL);
	sshkey_free(k1);
	TEST_DONE();
#endif

	TEST_START("fuzz Ed25519 sig");
	buf = load_file("ed25519_1");
	ASSERT_INT_EQ(sshkey_parse_private_fileblob(buf, "", &k1, NULL), 0);
	sshbuf_free(buf);
	sig_fuzz(k1, NULL);
	sshkey_free(k1);
	TEST_DONE();

/* XXX fuzz decoded new-format blobs too */

}