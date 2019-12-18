#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/ * hdb_master_key ;
typedef  int /*<<< orphan*/  hdb_entry ;
struct TYPE_13__ {int /*<<< orphan*/  hdb_master_key; scalar_t__ hdb_master_key_set; } ;
struct TYPE_9__ {int /*<<< orphan*/  password; int /*<<< orphan*/ * mkvno; } ;
struct TYPE_10__ {TYPE_1__ password; } ;
struct TYPE_11__ {TYPE_2__ u; int /*<<< orphan*/  element; } ;
struct TYPE_12__ {TYPE_3__ data; int /*<<< orphan*/  mandatory; } ;
typedef  TYPE_4__ HDB_extension ;
typedef  TYPE_5__ HDB ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int HDB_ERR_NO_MKEY ; 
 int /*<<< orphan*/  HDB_KU_MKEY ; 
 int /*<<< orphan*/ * _hdb_find_master_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int _hdb_mkey_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _hdb_mkey_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  choice_HDB_extension_data_password ; 
 int /*<<< orphan*/  free_HDB_extension (TYPE_4__*) ; 
 int hdb_replace_extension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int krb5_data_copy (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ strlen (char const*) ; 

int
hdb_entry_set_password(krb5_context context, HDB *db,
		       hdb_entry *entry, const char *p)
{
    HDB_extension ext;
    hdb_master_key key;
    int ret;

    ext.mandatory = FALSE;
    ext.data.element = choice_HDB_extension_data_password;

    if (db->hdb_master_key_set) {

	key = _hdb_find_master_key(NULL, db->hdb_master_key);
	if (key == NULL) {
	    krb5_set_error_message(context, HDB_ERR_NO_MKEY,
				   "hdb_entry_set_password: "
				   "failed to find masterkey");
	    return HDB_ERR_NO_MKEY;
	}

	ret = _hdb_mkey_encrypt(context, key, HDB_KU_MKEY,
				p, strlen(p) + 1,
				&ext.data.u.password.password);
	if (ret)
	    return ret;

	ext.data.u.password.mkvno =
	    malloc(sizeof(*ext.data.u.password.mkvno));
	if (ext.data.u.password.mkvno == NULL) {
	    free_HDB_extension(&ext);
	    krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	    return ENOMEM;
	}
	*ext.data.u.password.mkvno = _hdb_mkey_version(key);

    } else {
	ext.data.u.password.mkvno = NULL;

	ret = krb5_data_copy(&ext.data.u.password.password,
			     p, strlen(p) + 1);
	if (ret) {
	    krb5_set_error_message(context, ret, "malloc: out of memory");
	    free_HDB_extension(&ext);
	    return ret;
	}
    }

    ret = hdb_replace_extension(context, entry, &ext);

    free_HDB_extension(&ext);

    return ret;
}