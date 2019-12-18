#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ num_strings; } ;
struct TYPE_15__ {scalar_t__ num_strings; } ;
struct TYPE_14__ {scalar_t__ num_strings; } ;
struct modify_options {int kvno_integer; TYPE_9__ pkinit_acl_strings; TYPE_13__ alias_strings; TYPE_11__ constrained_delegation_strings; scalar_t__ attributes_string; scalar_t__ pw_expiration_time_string; scalar_t__ expiration_time_string; scalar_t__ max_renewable_life_string; scalar_t__ max_ticket_life_string; } ;
typedef  int /*<<< orphan*/  princ ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int krb5_error_code ;
struct TYPE_16__ {int kvno; } ;
typedef  TYPE_1__ kadm5_principal_ent_rec ;

/* Variables and functions */
 int KADM5_ATTRIBUTES ; 
 int KADM5_KVNO ; 
 int KADM5_MAX_LIFE ; 
 int KADM5_MAX_RLIFE ; 
 int KADM5_PRINCIPAL ; 
 int KADM5_PRINC_EXPIRE_TIME ; 
 int KADM5_PW_EXPIRATION ; 
 int KADM5_TL_DATA ; 
 int /*<<< orphan*/  add_aliases (int /*<<< orphan*/ ,TYPE_1__*,TYPE_13__*) ; 
 int /*<<< orphan*/  add_constrained_delegation (int /*<<< orphan*/ ,TYPE_1__*,TYPE_11__*) ; 
 int /*<<< orphan*/  add_pkinit_acl (int /*<<< orphan*/ ,TYPE_1__*,TYPE_9__*) ; 
 int /*<<< orphan*/  context ; 
 int edit_entry (TYPE_1__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kadm5_free_principal_ent (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int kadm5_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int kadm5_modify_principal (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  kadm_handle ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int set_entry (int /*<<< orphan*/ ,TYPE_1__*,int*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
do_mod_entry(krb5_principal principal, void *data)
{
    krb5_error_code ret;
    kadm5_principal_ent_rec princ;
    int mask = 0;
    struct modify_options *e = data;

    memset (&princ, 0, sizeof(princ));
    ret = kadm5_get_principal(kadm_handle, principal, &princ,
			      KADM5_PRINCIPAL | KADM5_ATTRIBUTES |
			      KADM5_MAX_LIFE | KADM5_MAX_RLIFE |
			      KADM5_PRINC_EXPIRE_TIME |
			      KADM5_PW_EXPIRATION);
    if(ret)
	return ret;

    if(e->max_ticket_life_string ||
       e->max_renewable_life_string ||
       e->expiration_time_string ||
       e->pw_expiration_time_string ||
       e->attributes_string ||
       e->kvno_integer != -1 ||
       e->constrained_delegation_strings.num_strings ||
       e->alias_strings.num_strings ||
       e->pkinit_acl_strings.num_strings) {
	ret = set_entry(context, &princ, &mask,
			e->max_ticket_life_string,
			e->max_renewable_life_string,
			e->expiration_time_string,
			e->pw_expiration_time_string,
			e->attributes_string);
	if(e->kvno_integer != -1) {
	    princ.kvno = e->kvno_integer;
	    mask |= KADM5_KVNO;
	}
	if (e->constrained_delegation_strings.num_strings) {
	    add_constrained_delegation(context, &princ,
				       &e->constrained_delegation_strings);
	    mask |= KADM5_TL_DATA;
	}
	if (e->alias_strings.num_strings) {
	    add_aliases(context, &princ, &e->alias_strings);
	    mask |= KADM5_TL_DATA;
	}
	if (e->pkinit_acl_strings.num_strings) {
	    add_pkinit_acl(context, &princ, &e->pkinit_acl_strings);
	    mask |= KADM5_TL_DATA;
	}

    } else
	ret = edit_entry(&princ, &mask, NULL, 0);
    if(ret == 0) {
	ret = kadm5_modify_principal(kadm_handle, &princ, mask);
	if(ret)
	    krb5_warn(context, ret, "kadm5_modify_principal");
    }

    kadm5_free_principal_ent(kadm_handle, &princ);
    return ret;
}