#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct get_entry_data {int mask; int extra_mask; int /*<<< orphan*/  (* format ) (struct get_entry_data*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  princ ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  kadm5_principal_ent_rec ;

/* Variables and functions */
 int /*<<< orphan*/  kadm5_free_principal_ent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kadm5_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kadm_handle ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct get_entry_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
do_get_entry(krb5_principal principal, void *data)
{
    kadm5_principal_ent_rec princ;
    krb5_error_code ret;
    struct get_entry_data *e = data;

    memset(&princ, 0, sizeof(princ));
    ret = kadm5_get_principal(kadm_handle, principal,
			      &princ,
			      e->mask | e->extra_mask);
    if(ret)
	return ret;
    else {
	(e->format)(e, &princ);
	kadm5_free_principal_ent(kadm_handle, &princ);
    }
    return 0;
}