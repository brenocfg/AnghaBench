#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_12__ {unsigned char* data; int length; } ;
typedef  TYPE_3__ heim_octet_string ;
struct TYPE_11__ {unsigned char* data; int length; } ;
struct TYPE_13__ {TYPE_2__ subjectPublicKey; } ;
struct TYPE_10__ {TYPE_4__ subjectPublicKeyInfo; } ;
struct TYPE_14__ {TYPE_1__ tbsCertificate; } ;
typedef  TYPE_4__ SubjectPublicKeyInfo ;
typedef  int /*<<< orphan*/  RSA ;
typedef  TYPE_5__ Certificate ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OID_ID_PKCS1_RSAENCRYPTION ; 
 int ENOMEM ; 
 int HX509_CRYPTO_RSA_PUBLIC_ENCRYPT ; 
 int /*<<< orphan*/  RSA_PKCS1_PADDING ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int RSA_public_encrypt (int,unsigned char*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RSA_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _hx509_abort (char*) ; 
 int /*<<< orphan*/ * d2i_RSAPublicKey (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 int der_copy_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  der_free_octet_string (TYPE_3__*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 unsigned char* malloc (int) ; 

int
_hx509_public_encrypt(hx509_context context,
		      const heim_octet_string *cleartext,
		      const Certificate *cert,
		      heim_oid *encryption_oid,
		      heim_octet_string *ciphertext)
{
    const SubjectPublicKeyInfo *spi;
    unsigned char *to;
    int tosize;
    int ret;
    RSA *rsa;
    size_t size;
    const unsigned char *p;

    ciphertext->data = NULL;
    ciphertext->length = 0;

    spi = &cert->tbsCertificate.subjectPublicKeyInfo;

    p = spi->subjectPublicKey.data;
    size = spi->subjectPublicKey.length / 8;

    rsa = d2i_RSAPublicKey(NULL, &p, size);
    if (rsa == NULL) {
	hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	return ENOMEM;
    }

    tosize = RSA_size(rsa);
    to = malloc(tosize);
    if (to == NULL) {
	RSA_free(rsa);
	hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	return ENOMEM;
    }

    ret = RSA_public_encrypt(cleartext->length,
			     (unsigned char *)cleartext->data,
			     to, rsa, RSA_PKCS1_PADDING);
    RSA_free(rsa);
    if (ret <= 0) {
	free(to);
	hx509_set_error_string(context, 0, HX509_CRYPTO_RSA_PUBLIC_ENCRYPT,
			       "RSA public encrypt failed with %d", ret);
	return HX509_CRYPTO_RSA_PUBLIC_ENCRYPT;
    }
    if (ret > tosize)
	_hx509_abort("internal rsa decryption failure: ret > tosize");

    ciphertext->length = ret;
    ciphertext->data = to;

    ret = der_copy_oid(ASN1_OID_ID_PKCS1_RSAENCRYPTION, encryption_oid);
    if (ret) {
	der_free_octet_string(ciphertext);
	hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	return ENOMEM;
    }

    return 0;
}