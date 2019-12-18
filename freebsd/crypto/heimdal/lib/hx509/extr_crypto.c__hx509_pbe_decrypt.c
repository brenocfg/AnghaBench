#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct _hx509_password {int len; char** val; } ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  iv ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_crypto ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_16__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ heim_octet_string ;
struct TYPE_17__ {int /*<<< orphan*/  parameters; int /*<<< orphan*/  algorithm; } ;
typedef  int (* PBE_string2key_func ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  TYPE_4__ AlgorithmIdentifier ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVP_CIPHER_iv_length (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_CIPHER_key_length (int /*<<< orphan*/  const*) ; 
 int HX509_ALG_NOT_SUPP ; 
 int HX509_CRYPTO_INTERNAL_ERROR ; 
 struct _hx509_password* _hx509_lock_get_passwords (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  der_free_octet_string (TYPE_1__*) ; 
 int /*<<< orphan*/ * find_string2key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int (*) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*)) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int hx509_crypto_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_crypto_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int
_hx509_pbe_decrypt(hx509_context context,
		   hx509_lock lock,
		   const AlgorithmIdentifier *ai,
		   const heim_octet_string *econtent,
		   heim_octet_string *content)
{
    const struct _hx509_password *pw;
    heim_octet_string key, iv;
    const heim_oid *enc_oid;
    const EVP_CIPHER *c;
    const EVP_MD *md;
    PBE_string2key_func s2k;
    int ret = 0;
    size_t i;

    memset(&key, 0, sizeof(key));
    memset(&iv, 0, sizeof(iv));

    memset(content, 0, sizeof(*content));

    enc_oid = find_string2key(&ai->algorithm, &c, &md, &s2k);
    if (enc_oid == NULL) {
	hx509_set_error_string(context, 0, HX509_ALG_NOT_SUPP,
			       "String to key algorithm not supported");
	ret = HX509_ALG_NOT_SUPP;
	goto out;
    }

    key.length = EVP_CIPHER_key_length(c);
    key.data = malloc(key.length);
    if (key.data == NULL) {
	ret = ENOMEM;
	hx509_clear_error_string(context);
	goto out;
    }

    iv.length = EVP_CIPHER_iv_length(c);
    iv.data = malloc(iv.length);
    if (iv.data == NULL) {
	ret = ENOMEM;
	hx509_clear_error_string(context);
	goto out;
    }

    pw = _hx509_lock_get_passwords(lock);

    ret = HX509_CRYPTO_INTERNAL_ERROR;
    for (i = 0; i < pw->len + 1; i++) {
	hx509_crypto crypto;
	const char *password;

	if (i < pw->len)
	    password = pw->val[i];
	else if (i < pw->len + 1)
	    password = "";
	else
	    password = NULL;

	ret = (*s2k)(context, password, ai->parameters, &crypto,
		     &key, &iv, enc_oid, md);
	if (ret)
	    goto out;

	ret = hx509_crypto_decrypt(crypto,
				   econtent->data,
				   econtent->length,
				   &iv,
				   content);
	hx509_crypto_destroy(crypto);
	if (ret == 0)
	    goto out;

    }
out:
    if (key.data)
	der_free_octet_string(&key);
    if (iv.data)
	der_free_octet_string(&iv);
    return ret;
}