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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  krb5_salt ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {TYPE_3__ keyvalue; int /*<<< orphan*/  keytype; } ;
typedef  TYPE_1__ krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_md4 () ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ krb5_data_alloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int* malloc (size_t) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ wind_utf8ucs2 (int /*<<< orphan*/ ,int*,size_t*) ; 
 scalar_t__ wind_utf8ucs2_length (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static krb5_error_code
ARCFOUR_string_to_key(krb5_context context,
		      krb5_enctype enctype,
		      krb5_data password,
		      krb5_salt salt,
		      krb5_data opaque,
		      krb5_keyblock *key)
{
    krb5_error_code ret;
    uint16_t *s = NULL;
    size_t len = 0, i;
    EVP_MD_CTX *m;

    m = EVP_MD_CTX_create();
    if (m == NULL) {
	ret = ENOMEM;
	krb5_set_error_message(context, ret, N_("malloc: out of memory", ""));
	goto out;
    }

    EVP_DigestInit_ex(m, EVP_md4(), NULL);

    ret = wind_utf8ucs2_length(password.data, &len);
    if (ret) {
	krb5_set_error_message (context, ret,
				N_("Password not an UCS2 string", ""));
	goto out;
    }

    s = malloc (len * sizeof(s[0]));
    if (len != 0 && s == NULL) {
	krb5_set_error_message (context, ENOMEM,
				N_("malloc: out of memory", ""));
	ret = ENOMEM;
	goto out;
    }

    ret = wind_utf8ucs2(password.data, s, &len);
    if (ret) {
	krb5_set_error_message (context, ret,
				N_("Password not an UCS2 string", ""));
	goto out;
    }

    /* LE encoding */
    for (i = 0; i < len; i++) {
	unsigned char p;
	p = (s[i] & 0xff);
	EVP_DigestUpdate (m, &p, 1);
	p = (s[i] >> 8) & 0xff;
	EVP_DigestUpdate (m, &p, 1);
    }

    key->keytype = enctype;
    ret = krb5_data_alloc (&key->keyvalue, 16);
    if (ret) {
	krb5_set_error_message (context, ENOMEM, N_("malloc: out of memory", ""));
	goto out;
    }
    EVP_DigestFinal_ex (m, key->keyvalue.data, NULL);

 out:
    EVP_MD_CTX_destroy(m);
    if (s)
	memset (s, 0, len);
    free (s);
    return ret;
}