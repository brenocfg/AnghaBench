#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_context ;
typedef  char* heim_utf8_string ;
struct TYPE_20__ {char* data; int length; } ;
typedef  TYPE_4__ heim_octet_string ;
typedef  int /*<<< orphan*/ * hdb_master_key ;
struct TYPE_21__ {int /*<<< orphan*/  principal; } ;
typedef  TYPE_5__ hdb_entry ;
struct TYPE_23__ {int /*<<< orphan*/  hdb_master_key; scalar_t__ hdb_master_key_set; } ;
struct TYPE_16__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_17__ {char** mkvno; TYPE_13__ password; } ;
struct TYPE_18__ {TYPE_1__ password; } ;
struct TYPE_19__ {TYPE_2__ u; } ;
struct TYPE_22__ {TYPE_3__ data; } ;
typedef  TYPE_6__ HDB_extension ;
typedef  TYPE_7__ HDB ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int HDB_ERR_NO_MKEY ; 
 int /*<<< orphan*/  HDB_KU_MKEY ; 
 int /*<<< orphan*/ * _hdb_find_master_key (char**,int /*<<< orphan*/ ) ; 
 int _hdb_mkey_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  choice_HDB_extension_data_password ; 
 int der_copy_octet_string (TYPE_13__*,TYPE_4__*) ; 
 int /*<<< orphan*/  der_free_octet_string (TYPE_4__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_6__* hdb_find_extension (TYPE_5__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,char*,...) ; 
 int krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 char* strdup (char*) ; 

int
hdb_entry_get_password(krb5_context context, HDB *db,
		       const hdb_entry *entry, char **p)
{
    HDB_extension *ext;
    char *str;
    int ret;

    ext = hdb_find_extension(entry, choice_HDB_extension_data_password);
    if (ext) {
	heim_utf8_string xstr;
	heim_octet_string pw;

	if (db->hdb_master_key_set && ext->data.u.password.mkvno) {
	    hdb_master_key key;

	    key = _hdb_find_master_key(ext->data.u.password.mkvno,
				       db->hdb_master_key);

	    if (key == NULL) {
		krb5_set_error_message(context, HDB_ERR_NO_MKEY,
				       "master key %d missing",
				       *ext->data.u.password.mkvno);
		return HDB_ERR_NO_MKEY;
	    }

	    ret = _hdb_mkey_decrypt(context, key, HDB_KU_MKEY,
				    ext->data.u.password.password.data,
				    ext->data.u.password.password.length,
				    &pw);
	} else {
	    ret = der_copy_octet_string(&ext->data.u.password.password, &pw);
	}
	if (ret) {
	    krb5_clear_error_message(context);
	    return ret;
	}

	xstr = pw.data;
	if (xstr[pw.length - 1] != '\0') {
	    krb5_set_error_message(context, EINVAL, "malformed password");
	    return EINVAL;
	}

	*p = strdup(xstr);

	der_free_octet_string(&pw);
	if (*p == NULL) {
	    krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	    return ENOMEM;
	}
	return 0;
    }

    ret = krb5_unparse_name(context, entry->principal, &str);
    if (ret == 0) {
	krb5_set_error_message(context, ENOENT,
			       "no password attribute for %s", str);
	free(str);
    } else
	krb5_clear_error_message(context);

    return ENOENT;
}