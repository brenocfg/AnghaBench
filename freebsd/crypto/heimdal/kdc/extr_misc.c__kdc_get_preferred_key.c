#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ use_strongest_server_key; } ;
typedef  TYPE_5__ krb5_kdc_configuration ;
typedef  scalar_t__ krb5_error_code ;
typedef  scalar_t__ krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_15__ {int len; TYPE_2__* val; } ;
struct TYPE_20__ {TYPE_3__ keys; } ;
struct TYPE_18__ {TYPE_8__ entry; } ;
typedef  TYPE_6__ hdb_entry_ex ;
struct TYPE_16__ {scalar_t__ keytype; } ;
struct TYPE_19__ {TYPE_4__ key; } ;
struct TYPE_13__ {scalar_t__ const keytype; } ;
struct TYPE_14__ {TYPE_1__ key; } ;
typedef  TYPE_7__ Key ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ const ETYPE_NULL ; 
 scalar_t__ hdb_enctype2key (int /*<<< orphan*/ ,TYPE_8__*,scalar_t__ const,TYPE_7__**) ; 
 scalar_t__ krb5_enctype_valid (int /*<<< orphan*/ ,scalar_t__ const) ; 
 scalar_t__* krb5_kerberos_enctypes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*,char const*) ; 

krb5_error_code
_kdc_get_preferred_key(krb5_context context,
		       krb5_kdc_configuration *config,
		       hdb_entry_ex *h,
		       const char *name,
		       krb5_enctype *enctype,
		       Key **key)
{
    krb5_error_code ret;
    int i;

    if (config->use_strongest_server_key) {
	const krb5_enctype *p = krb5_kerberos_enctypes(context);

	for (i = 0; p[i] != ETYPE_NULL; i++) {
	    if (krb5_enctype_valid(context, p[i]) != 0)
		continue;
	    ret = hdb_enctype2key(context, &h->entry, p[i], key);
	    if (ret != 0)
		continue;
	    if (enctype != NULL)
		*enctype = p[i];
	    return 0;
	}
    } else {
	*key = NULL;

	for (i = 0; i < h->entry.keys.len; i++) {
	    if (krb5_enctype_valid(context, h->entry.keys.val[i].key.keytype)
		!= 0)
		continue;
	    ret = hdb_enctype2key(context, &h->entry,
		h->entry.keys.val[i].key.keytype, key);
	    if (ret != 0)
		continue;
	    if (enctype != NULL)
		*enctype = (*key)->key.keytype;
	    return 0;
	}
    }

    krb5_set_error_message(context, EINVAL,
			   "No valid kerberos key found for %s", name);
    return EINVAL; /* XXX */
}