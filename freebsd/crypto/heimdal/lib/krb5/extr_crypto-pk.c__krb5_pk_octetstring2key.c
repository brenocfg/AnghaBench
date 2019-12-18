#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _krb5_encryption_type {TYPE_1__* keytype; } ;
typedef  int /*<<< orphan*/  shaoutput ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  keylen ;
struct TYPE_6__ {void const* data; size_t length; } ;
typedef  TYPE_2__ heim_octet_string ;
struct TYPE_5__ {int bits; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  KRB5_PROG_ETYPE_NOSUPP ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int SHA_DIGEST_LENGTH ; 
 struct _krb5_encryption_type* _krb5_find_enctype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  krb5_random_to_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (size_t,int) ; 

krb5_error_code
_krb5_pk_octetstring2key(krb5_context context,
			 krb5_enctype type,
			 const void *dhdata,
			 size_t dhsize,
			 const heim_octet_string *c_n,
			 const heim_octet_string *k_n,
			 krb5_keyblock *key)
{
    struct _krb5_encryption_type *et = _krb5_find_enctype(type);
    krb5_error_code ret;
    size_t keylen, offset;
    void *keydata;
    unsigned char counter;
    unsigned char shaoutput[SHA_DIGEST_LENGTH];
    EVP_MD_CTX *m;

    if(et == NULL) {
	krb5_set_error_message(context, KRB5_PROG_ETYPE_NOSUPP,
			       N_("encryption type %d not supported", ""),
			       type);
	return KRB5_PROG_ETYPE_NOSUPP;
    }
    keylen = (et->keytype->bits + 7) / 8;

    keydata = malloc(keylen);
    if (keydata == NULL) {
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }

    m = EVP_MD_CTX_create();
    if (m == NULL) {
	free(keydata);
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }

    counter = 0;
    offset = 0;
    do {

	EVP_DigestInit_ex(m, EVP_sha1(), NULL);
	EVP_DigestUpdate(m, &counter, 1);
	EVP_DigestUpdate(m, dhdata, dhsize);

	if (c_n)
	    EVP_DigestUpdate(m, c_n->data, c_n->length);
	if (k_n)
	    EVP_DigestUpdate(m, k_n->data, k_n->length);

	EVP_DigestFinal_ex(m, shaoutput, NULL);

	memcpy((unsigned char *)keydata + offset,
	       shaoutput,
	       min(keylen - offset, sizeof(shaoutput)));

	offset += sizeof(shaoutput);
	counter++;
    } while(offset < keylen);
    memset(shaoutput, 0, sizeof(shaoutput));

    EVP_MD_CTX_destroy(m);

    ret = krb5_random_to_key(context, type, keydata, keylen, key);
    memset(keydata, 0, sizeof(keylen));
    free(keydata);
    return ret;
}