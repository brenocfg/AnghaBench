#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {struct TYPE_5__* tl_data_next; } ;
typedef  TYPE_1__ krb5_tl_data ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;
typedef  TYPE_2__* kadm5_principal_ent_t ;
struct TYPE_6__ {int princ_expire_time; int pw_expiration; int last_pwd_change; int max_life; int mod_date; int attributes; int kvno; int mkvno; int aux_attributes; int max_renewable_life; int last_success; int last_failed; int fail_auth_count; int n_key_data; int n_tl_data; TYPE_1__* tl_data; int /*<<< orphan*/ * key_data; int /*<<< orphan*/ * policy; int /*<<< orphan*/ * mod_name; int /*<<< orphan*/ * principal; } ;

/* Variables and functions */
 int KADM5_ATTRIBUTES ; 
 int KADM5_AUX_ATTRIBUTES ; 
 int KADM5_FAIL_AUTH_COUNT ; 
 int KADM5_KEY_DATA ; 
 int KADM5_KVNO ; 
 int KADM5_LAST_FAILED ; 
 int KADM5_LAST_PWD_CHANGE ; 
 int KADM5_LAST_SUCCESS ; 
 int KADM5_MAX_LIFE ; 
 int KADM5_MAX_RLIFE ; 
 int KADM5_MKVNO ; 
 int KADM5_MOD_NAME ; 
 int KADM5_MOD_TIME ; 
 int KADM5_POLICY ; 
 int KADM5_PRINCIPAL ; 
 int KADM5_PRINC_EXPIRE_TIME ; 
 int KADM5_PW_EXPIRATION ; 
 int KADM5_TL_DATA ; 
 int /*<<< orphan*/  kadm5_store_key_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm5_store_tl_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  krb5_store_principal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_store_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static kadm5_ret_t
store_principal_ent(krb5_storage *sp,
		    kadm5_principal_ent_t princ,
		    uint32_t mask)
{
    int i;

    if (mask & KADM5_PRINCIPAL)
	krb5_store_principal(sp, princ->principal);
    if (mask & KADM5_PRINC_EXPIRE_TIME)
	krb5_store_int32(sp, princ->princ_expire_time);
    if (mask & KADM5_PW_EXPIRATION)
	krb5_store_int32(sp, princ->pw_expiration);
    if (mask & KADM5_LAST_PWD_CHANGE)
	krb5_store_int32(sp, princ->last_pwd_change);
    if (mask & KADM5_MAX_LIFE)
	krb5_store_int32(sp, princ->max_life);
    if (mask & KADM5_MOD_NAME) {
	krb5_store_int32(sp, princ->mod_name != NULL);
	if(princ->mod_name)
	    krb5_store_principal(sp, princ->mod_name);
    }
    if (mask & KADM5_MOD_TIME)
	krb5_store_int32(sp, princ->mod_date);
    if (mask & KADM5_ATTRIBUTES)
	krb5_store_int32(sp, princ->attributes);
    if (mask & KADM5_KVNO)
	krb5_store_int32(sp, princ->kvno);
    if (mask & KADM5_MKVNO)
	krb5_store_int32(sp, princ->mkvno);
    if (mask & KADM5_POLICY) {
	krb5_store_int32(sp, princ->policy != NULL);
	if(princ->policy)
	    krb5_store_string(sp, princ->policy);
    }
    if (mask & KADM5_AUX_ATTRIBUTES)
	krb5_store_int32(sp, princ->aux_attributes);
    if (mask & KADM5_MAX_RLIFE)
	krb5_store_int32(sp, princ->max_renewable_life);
    if (mask & KADM5_LAST_SUCCESS)
	krb5_store_int32(sp, princ->last_success);
    if (mask & KADM5_LAST_FAILED)
	krb5_store_int32(sp, princ->last_failed);
    if (mask & KADM5_FAIL_AUTH_COUNT)
	krb5_store_int32(sp, princ->fail_auth_count);
    if (mask & KADM5_KEY_DATA) {
	krb5_store_int32(sp, princ->n_key_data);
	for(i = 0; i < princ->n_key_data; i++)
	    kadm5_store_key_data(sp, &princ->key_data[i]);
    }
    if (mask & KADM5_TL_DATA) {
	krb5_tl_data *tp;

	krb5_store_int32(sp, princ->n_tl_data);
	for(tp = princ->tl_data; tp; tp = tp->tl_data_next)
	    kadm5_store_tl_data(sp, tp);
    }
    return 0;
}