#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct _krb5_key_data {int dummy; } ;
struct _krb5_checksum_type {int flags; scalar_t__ checksumsize; scalar_t__ type; int /*<<< orphan*/  name; scalar_t__ (* checksum ) (int /*<<< orphan*/ ,struct _krb5_key_data*,void*,size_t,unsigned int,TYPE_3__*) ;scalar_t__ (* verify ) (int /*<<< orphan*/ ,struct _krb5_key_data*,void*,size_t,unsigned int,TYPE_3__*) ;} ;
typedef  scalar_t__ krb5_error_code ;
typedef  TYPE_2__* krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_16__ {scalar_t__ length; } ;
struct TYPE_15__ {TYPE_8__ checksum; int /*<<< orphan*/  cksumtype; } ;
struct TYPE_14__ {TYPE_1__* et; } ;
struct TYPE_13__ {char* name; struct _krb5_checksum_type* keyed_checksum; } ;
typedef  TYPE_3__ Checksum ;

/* Variables and functions */
 int F_DISABLED ; 
 int F_KEYED ; 
 scalar_t__ KRB5KRB_AP_ERR_BAD_INTEGRITY ; 
 scalar_t__ KRB5_PROG_SUMTYPE_NOSUPP ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 struct _krb5_checksum_type* _krb5_find_checksum (int /*<<< orphan*/ ) ; 
 scalar_t__ get_checksum_key (int /*<<< orphan*/ ,TYPE_2__*,unsigned int,struct _krb5_checksum_type*,struct _krb5_key_data**) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_data_alloc (TYPE_8__*,scalar_t__) ; 
 scalar_t__ krb5_data_ct_cmp (TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_8__*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,struct _krb5_key_data*,void*,size_t,unsigned int,TYPE_3__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,struct _krb5_key_data*,void*,size_t,unsigned int,TYPE_3__*) ; 

__attribute__((used)) static krb5_error_code
verify_checksum(krb5_context context,
		krb5_crypto crypto,
		unsigned usage, /* not krb5_key_usage */
		void *data,
		size_t len,
		Checksum *cksum)
{
    krb5_error_code ret;
    struct _krb5_key_data *dkey;
    int keyed_checksum;
    Checksum c;
    struct _krb5_checksum_type *ct;

    ct = _krb5_find_checksum(cksum->cksumtype);
    if (ct == NULL || (ct->flags & F_DISABLED)) {
	krb5_set_error_message (context, KRB5_PROG_SUMTYPE_NOSUPP,
				N_("checksum type %d not supported", ""),
				cksum->cksumtype);
	return KRB5_PROG_SUMTYPE_NOSUPP;
    }
    if(ct->checksumsize != cksum->checksum.length) {
	krb5_clear_error_message (context);
	krb5_set_error_message(context, KRB5KRB_AP_ERR_BAD_INTEGRITY,
			       N_("Decrypt integrity check failed for checksum type %s, "
				  "length was %u, expected %u", ""),
			       ct->name, (unsigned)cksum->checksum.length,
			       (unsigned)ct->checksumsize);

	return KRB5KRB_AP_ERR_BAD_INTEGRITY; /* XXX */
    }
    keyed_checksum = (ct->flags & F_KEYED) != 0;
    if(keyed_checksum) {
	struct _krb5_checksum_type *kct;
	if (crypto == NULL) {
	    krb5_set_error_message(context, KRB5_PROG_SUMTYPE_NOSUPP,
				   N_("Checksum type %s is keyed but no "
				      "crypto context (key) was passed in", ""),
				   ct->name);
	    return KRB5_PROG_SUMTYPE_NOSUPP; /* XXX */
	}
	kct = crypto->et->keyed_checksum;
	if (kct == NULL || kct->type != ct->type) {
	    krb5_set_error_message(context, KRB5_PROG_SUMTYPE_NOSUPP,
				   N_("Checksum type %s is keyed, but "
				      "the key type %s passed didnt have that checksum "
				      "type as the keyed type", ""),
				    ct->name, crypto->et->name);
	    return KRB5_PROG_SUMTYPE_NOSUPP; /* XXX */
	}

	ret = get_checksum_key(context, crypto, usage, ct, &dkey);
	if (ret)
	    return ret;
    } else
	dkey = NULL;

    /*
     * If checksum have a verify function, lets use that instead of
     * calling ->checksum and then compare result.
     */

    if(ct->verify) {
	ret = (*ct->verify)(context, dkey, data, len, usage, cksum);
	if (ret)
	    krb5_set_error_message(context, ret,
				   N_("Decrypt integrity check failed for checksum "
				      "type %s, key type %s", ""),
				   ct->name, (crypto != NULL)? crypto->et->name : "(none)");
	return ret;
    }

    ret = krb5_data_alloc (&c.checksum, ct->checksumsize);
    if (ret)
	return ret;

    ret = (*ct->checksum)(context, dkey, data, len, usage, &c);
    if (ret) {
	krb5_data_free(&c.checksum);
	return ret;
    }

    if(krb5_data_ct_cmp(&c.checksum, &cksum->checksum) != 0) {
	ret = KRB5KRB_AP_ERR_BAD_INTEGRITY;
	krb5_set_error_message(context, ret,
			       N_("Decrypt integrity check failed for checksum "
				  "type %s, key type %s", ""),
			       ct->name, crypto ? crypto->et->name : "(unkeyed)");
    } else {
	ret = 0;
    }
    krb5_data_free (&c.checksum);
    return ret;
}