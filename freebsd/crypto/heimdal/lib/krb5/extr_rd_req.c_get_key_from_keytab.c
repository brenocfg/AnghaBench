#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  keyblock; } ;
typedef  TYPE_3__ krb5_keytab_entry ;
typedef  int /*<<< orphan*/ * krb5_keytab ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_const_principal ;
struct TYPE_8__ {int* kvno; int /*<<< orphan*/  etype; } ;
struct TYPE_9__ {TYPE_1__ enc_part; } ;
struct TYPE_11__ {TYPE_2__ ticket; } ;
typedef  TYPE_4__ krb5_ap_req ;

/* Variables and functions */
 scalar_t__ krb5_copy_keyblock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_kt_default (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_kt_free_entry (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ krb5_kt_get_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static krb5_error_code
get_key_from_keytab(krb5_context context,
		    krb5_ap_req *ap_req,
		    krb5_const_principal server,
		    krb5_keytab keytab,
		    krb5_keyblock **out_key)
{
    krb5_keytab_entry entry;
    krb5_error_code ret;
    int kvno;
    krb5_keytab real_keytab;

    if(keytab == NULL)
	krb5_kt_default(context, &real_keytab);
    else
	real_keytab = keytab;

    if (ap_req->ticket.enc_part.kvno)
	kvno = *ap_req->ticket.enc_part.kvno;
    else
	kvno = 0;

    ret = krb5_kt_get_entry (context,
			     real_keytab,
			     server,
			     kvno,
			     ap_req->ticket.enc_part.etype,
			     &entry);
    if(ret)
	goto out;
    ret = krb5_copy_keyblock(context, &entry.keyblock, out_key);
    krb5_kt_free_entry (context, &entry);
out:
    if(keytab == NULL)
	krb5_kt_close(context, real_keytab);

    return ret;
}