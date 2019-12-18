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
typedef  scalar_t__ krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_7__ {int len; TYPE_4__* val; } ;
struct TYPE_9__ {TYPE_1__ keys; } ;
typedef  TYPE_3__ hdb_entry ;
struct TYPE_8__ {scalar_t__ keytype; } ;
struct TYPE_10__ {TYPE_2__ key; } ;
typedef  TYPE_4__ Key ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_PROG_ETYPE_NOSUPP ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

krb5_error_code
hdb_next_enctype2key(krb5_context context,
		     const hdb_entry *e,
		     krb5_enctype enctype,
		     Key **key)
{
    Key *k;

    for (k = *key ? (*key) + 1 : e->keys.val;
	 k < e->keys.val + e->keys.len;
	 k++)
    {
	if(k->key.keytype == enctype){
	    *key = k;
	    return 0;
	}
    }
    krb5_set_error_message(context, KRB5_PROG_ETYPE_NOSUPP,
			   "No next enctype %d for hdb-entry",
			  (int)enctype);
    return KRB5_PROG_ETYPE_NOSUPP; /* XXX */
}