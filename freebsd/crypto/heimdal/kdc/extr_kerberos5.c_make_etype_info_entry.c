#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_10__ {int* salttype; int /*<<< orphan*/ * salt; int /*<<< orphan*/  etype; } ;
struct TYPE_7__ {int /*<<< orphan*/  keytype; } ;
struct TYPE_9__ {TYPE_2__* salt; TYPE_1__ key; } ;
struct TYPE_8__ {int type; int /*<<< orphan*/  salt; } ;
typedef  TYPE_3__ Key ;
typedef  TYPE_4__ ETYPE_INFO_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC (int*) ; 
 int /*<<< orphan*/  KRB5KRB_ERR_GENERIC ; 
 int /*<<< orphan*/  config ; 
 int hdb_afs3_salt ; 
 int hdb_pw_salt ; 
 int /*<<< orphan*/  kdc_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  krb5_copy_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static krb5_error_code
make_etype_info_entry(krb5_context context, ETYPE_INFO_ENTRY *ent, Key *key)
{
    ent->etype = key->key.keytype;
    if(key->salt){
#if 0
	ALLOC(ent->salttype);

	if(key->salt->type == hdb_pw_salt)
	    *ent->salttype = 0; /* or 1? or NULL? */
	else if(key->salt->type == hdb_afs3_salt)
	    *ent->salttype = 2;
	else {
	    kdc_log(context, config, 0, "unknown salt-type: %d",
		    key->salt->type);
	    return KRB5KRB_ERR_GENERIC;
	}
	/* according to `the specs', we can't send a salt if
	   we have AFS3 salted key, but that requires that you
	   *know* what cell you are using (e.g by assuming
	   that the cell is the same as the realm in lower
	   case) */
#elif 0
	ALLOC(ent->salttype);
	*ent->salttype = key->salt->type;
#else
	/*
	 * We shouldn't sent salttype since it is incompatible with the
	 * specification and it breaks windows clients.  The afs
	 * salting problem is solved by using KRB5-PADATA-AFS3-SALT
	 * implemented in Heimdal 0.7 and later.
	 */
	ent->salttype = NULL;
#endif
	krb5_copy_data(context, &key->salt->salt,
		       &ent->salt);
    } else {
	/* we return no salt type at all, as that should indicate
	 * the default salt type and make everybody happy.  some
	 * systems (like w2k) dislike being told the salt type
	 * here. */

	ent->salttype = NULL;
	ent->salt = NULL;
    }
    return 0;
}