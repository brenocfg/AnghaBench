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
typedef  int /*<<< orphan*/  hx509_private_key ;
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int RSA_generate_key_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 size_t i2d_RSAPrivateKey (int /*<<< orphan*/ *,unsigned char**) ; 
 unsigned char* malloc (size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int read_private_key (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rk_dumpdata (char const*,unsigned char*,size_t) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static void
get_key(const char *fn, const char *type, int optbits,
	hx509_private_key *signer)
{
    int ret;

    if (type) {
	BIGNUM *e;
	RSA *rsa;
	unsigned char *p0, *p;
	size_t len;
	int bits = 1024;

	if (fn == NULL)
	    errx(1, "no key argument, don't know here to store key");

	if (strcasecmp(type, "rsa") != 0)
	    errx(1, "can only handle rsa keys for now");

	e = BN_new();
	BN_set_word(e, 0x10001);

	if (optbits)
	    bits = optbits;

	rsa = RSA_new();
	if(rsa == NULL)
	    errx(1, "RSA_new failed");

	ret = RSA_generate_key_ex(rsa, bits, e, NULL);
	if(ret != 1)
	    errx(1, "RSA_new failed");

	BN_free(e);

	len = i2d_RSAPrivateKey(rsa, NULL);

	p0 = p = malloc(len);
	if (p == NULL)
	    errx(1, "out of memory");

	i2d_RSAPrivateKey(rsa, &p);

	rk_dumpdata(fn, p0, len);
	memset(p0, 0, len);
	free(p0);

	RSA_free(rsa);

    } else if (fn == NULL)
	err(1, "no private key");

    ret = read_private_key(fn, signer);
    if (ret)
	err(1, "read_private_key");
}