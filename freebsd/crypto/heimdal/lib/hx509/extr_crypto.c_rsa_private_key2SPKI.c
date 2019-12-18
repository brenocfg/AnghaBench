#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_8__ {unsigned char* data; int length; } ;
struct TYPE_11__ {TYPE_1__ subjectPublicKey; int /*<<< orphan*/  algorithm; } ;
struct TYPE_9__ {int /*<<< orphan*/  rsa; } ;
struct TYPE_10__ {TYPE_2__ private_key; } ;
typedef  TYPE_4__ SubjectPublicKeyInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OID_ID_PKCS1_RSAENCRYPTION ; 
 int ENOMEM ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int i2d_RSAPublicKey (int /*<<< orphan*/ ,unsigned char**) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int set_digest_alg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
rsa_private_key2SPKI(hx509_context context,
		     hx509_private_key private_key,
		     SubjectPublicKeyInfo *spki)
{
    int len, ret;

    memset(spki, 0, sizeof(*spki));

    len = i2d_RSAPublicKey(private_key->private_key.rsa, NULL);

    spki->subjectPublicKey.data = malloc(len);
    if (spki->subjectPublicKey.data == NULL) {
	hx509_set_error_string(context, 0, ENOMEM, "malloc - out of memory");
	return ENOMEM;
    }
    spki->subjectPublicKey.length = len * 8;

    ret = set_digest_alg(&spki->algorithm, ASN1_OID_ID_PKCS1_RSAENCRYPTION,
			 "\x05\x00", 2);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "malloc - out of memory");
	free(spki->subjectPublicKey.data);
	spki->subjectPublicKey.data = NULL;
	spki->subjectPublicKey.length = 0;
	return ret;
    }

    {
	unsigned char *pp = spki->subjectPublicKey.data;
	i2d_RSAPublicKey(private_key->private_key.rsa, &pp);
    }

    return 0;
}