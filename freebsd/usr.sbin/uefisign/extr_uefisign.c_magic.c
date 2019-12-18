#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* sign; } ;
struct TYPE_9__ {TYPE_2__ d; } ;
struct TYPE_7__ {int /*<<< orphan*/  contents; } ;
typedef  TYPE_3__ PKCS7 ;
typedef  int /*<<< orphan*/  CONF ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_STRING_new () ; 
 int /*<<< orphan*/  ASN1_STRING_set (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/ * ASN1_TYPE_new () ; 
 int /*<<< orphan*/  ASN1_TYPE_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_generate_nconf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_mem_buf (void*,int) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,char*,char*) ; 
 int NCONF_load_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NCONF_new (int /*<<< orphan*/ *) ; 
 int OBJ_create (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PKCS7_dataFinal (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PKCS7_dataInit (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7_set0_type_other (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 
 int /*<<< orphan*/  asprintf (char**,int /*<<< orphan*/ ,char*) ; 
 char* bin2hex (char const*,size_t) ; 
 unsigned char* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int i2d_ASN1_TYPE (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  magic_fmt ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
magic(PKCS7 *pkcs7, const char *digest, size_t digest_len)
{
	BIO *bio, *t_bio;
	ASN1_TYPE *t;
	ASN1_STRING *s;
	CONF *cnf;
	unsigned char *buf, *tmp;
	char *digest_hex, *magic_conf, *str;
	int len, nid, ok;

	digest_hex = bin2hex(digest, digest_len);

	/*
	 * Construct the SpcIndirectDataContent chunk.
	 */
	nid = OBJ_create("1.3.6.1.4.1.311.2.1.4", NULL, NULL);

	asprintf(&magic_conf, magic_fmt, digest_hex);
	if (magic_conf == NULL)
		err(1, "asprintf");

	bio = BIO_new_mem_buf((void *)magic_conf, -1);
	if (bio == NULL) {
		ERR_print_errors_fp(stderr);
		errx(1, "BIO_new_mem_buf(3) failed");
	}

	cnf = NCONF_new(NULL);
	if (cnf == NULL) {
		ERR_print_errors_fp(stderr);
		errx(1, "NCONF_new(3) failed");
	}

	ok = NCONF_load_bio(cnf, bio, NULL);
	if (ok == 0) {
		ERR_print_errors_fp(stderr);
		errx(1, "NCONF_load_bio(3) failed");
	}

	str = NCONF_get_string(cnf, "default", "asn1");
	if (str == NULL) {
		ERR_print_errors_fp(stderr);
		errx(1, "NCONF_get_string(3) failed");
	}

	t = ASN1_generate_nconf(str, cnf);
	if (t == NULL) {
		ERR_print_errors_fp(stderr);
		errx(1, "ASN1_generate_nconf(3) failed");
	}

	/*
	 * We now have our proprietary piece of ASN.1.  Let's do
	 * the actual signing.
	 */
	len = i2d_ASN1_TYPE(t, NULL);
	tmp = buf = calloc(1, len);
	if (tmp == NULL)
		err(1, "calloc");
	i2d_ASN1_TYPE(t, &tmp);

	/*
	 * We now have contents of 't' stuffed into memory buffer 'buf'.
	 */
	tmp = NULL;
	t = NULL;

	t_bio = PKCS7_dataInit(pkcs7, NULL);
	if (t_bio == NULL) {
		ERR_print_errors_fp(stderr);
		errx(1, "PKCS7_dataInit(3) failed");
	}

	BIO_write(t_bio, buf + 2, len - 2);

	ok = PKCS7_dataFinal(pkcs7, t_bio);
	if (ok == 0) {
		ERR_print_errors_fp(stderr);
		errx(1, "PKCS7_dataFinal(3) failed");
	}

	t = ASN1_TYPE_new();
	s = ASN1_STRING_new();
	ASN1_STRING_set(s, buf, len);
	ASN1_TYPE_set(t, V_ASN1_SEQUENCE, s);

	PKCS7_set0_type_other(pkcs7->d.sign->contents, nid, t);
}