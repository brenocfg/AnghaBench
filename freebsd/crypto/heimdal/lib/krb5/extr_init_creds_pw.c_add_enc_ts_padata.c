#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_salt ;
typedef  scalar_t__ (* krb5_s2k_proc ) (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  scalar_t__ krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  TYPE_1__* krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_pointer ;
struct TYPE_11__ {scalar_t__* etypes; } ;
typedef  int /*<<< orphan*/  METHOD_DATA ;

/* Variables and functions */
 scalar_t__ ETYPE_NULL ; 
 int /*<<< orphan*/  _krb5_debug (TYPE_1__*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  krb5_free_keyblock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_salt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_get_pw_salt (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ make_pa_enc_timestamp (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static krb5_error_code
add_enc_ts_padata(krb5_context context,
		  METHOD_DATA *md,
		  krb5_principal client,
		  krb5_s2k_proc keyproc,
		  krb5_const_pointer keyseed,
		  krb5_enctype *enctypes,
		  unsigned netypes,
		  krb5_salt *salt,
		  krb5_data *s2kparams)
{
    krb5_error_code ret;
    krb5_salt salt2;
    krb5_enctype *ep;
    size_t i;

    if(salt == NULL) {
	/* default to standard salt */
	ret = krb5_get_pw_salt (context, client, &salt2);
	if (ret)
	    return ret;
	salt = &salt2;
    }
    if (!enctypes) {
	enctypes = context->etypes;
	netypes = 0;
	for (ep = enctypes; *ep != ETYPE_NULL; ep++)
	    netypes++;
    }

    for (i = 0; i < netypes; ++i) {
	krb5_keyblock *key;

	_krb5_debug(context, 5, "krb5_get_init_creds: using ENC-TS with enctype %d", enctypes[i]);

	ret = (*keyproc)(context, enctypes[i], keyseed,
			 *salt, s2kparams, &key);
	if (ret)
	    continue;
	ret = make_pa_enc_timestamp (context, md, enctypes[i], key);
	krb5_free_keyblock (context, key);
	if (ret)
	    return ret;
    }
    if(salt == &salt2)
	krb5_free_salt(context, salt2);
    return 0;
}