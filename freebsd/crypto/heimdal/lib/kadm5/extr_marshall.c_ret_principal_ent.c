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
typedef  void* int32_t ;
struct TYPE_6__ {int n_key_data; int n_tl_data; TYPE_1__* tl_data; int /*<<< orphan*/ * key_data; void* fail_auth_count; void* last_failed; void* last_success; void* max_renewable_life; void* aux_attributes; int /*<<< orphan*/ * policy; void* mkvno; void* kvno; void* attributes; void* mod_date; int /*<<< orphan*/ * mod_name; void* max_life; void* last_pwd_change; void* pw_expiration; void* princ_expire_time; int /*<<< orphan*/ * principal; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
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
 int /*<<< orphan*/  kadm5_ret_key_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm5_ret_tl_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_ret_int32 (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  krb5_ret_principal (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_ret_string (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 void* malloc (int) ; 

__attribute__((used)) static kadm5_ret_t
ret_principal_ent(krb5_storage *sp,
		  kadm5_principal_ent_t princ,
		  uint32_t mask)
{
    int i;
    int32_t tmp;

    if (mask & KADM5_PRINCIPAL)
	krb5_ret_principal(sp, &princ->principal);

    if (mask & KADM5_PRINC_EXPIRE_TIME) {
	krb5_ret_int32(sp, &tmp);
	princ->princ_expire_time = tmp;
    }
    if (mask & KADM5_PW_EXPIRATION) {
	krb5_ret_int32(sp, &tmp);
	princ->pw_expiration = tmp;
    }
    if (mask & KADM5_LAST_PWD_CHANGE) {
	krb5_ret_int32(sp, &tmp);
	princ->last_pwd_change = tmp;
    }
    if (mask & KADM5_MAX_LIFE) {
	krb5_ret_int32(sp, &tmp);
	princ->max_life = tmp;
    }
    if (mask & KADM5_MOD_NAME) {
	krb5_ret_int32(sp, &tmp);
	if(tmp)
	    krb5_ret_principal(sp, &princ->mod_name);
	else
	    princ->mod_name = NULL;
    }
    if (mask & KADM5_MOD_TIME) {
	krb5_ret_int32(sp, &tmp);
	princ->mod_date = tmp;
    }
    if (mask & KADM5_ATTRIBUTES) {
	krb5_ret_int32(sp, &tmp);
	princ->attributes = tmp;
    }
    if (mask & KADM5_KVNO) {
	krb5_ret_int32(sp, &tmp);
	princ->kvno = tmp;
    }
    if (mask & KADM5_MKVNO) {
	krb5_ret_int32(sp, &tmp);
	princ->mkvno = tmp;
    }
    if (mask & KADM5_POLICY) {
	krb5_ret_int32(sp, &tmp);
	if(tmp)
	    krb5_ret_string(sp, &princ->policy);
	else
	    princ->policy = NULL;
    }
    if (mask & KADM5_AUX_ATTRIBUTES) {
	krb5_ret_int32(sp, &tmp);
	princ->aux_attributes = tmp;
    }
    if (mask & KADM5_MAX_RLIFE) {
	krb5_ret_int32(sp, &tmp);
	princ->max_renewable_life = tmp;
    }
    if (mask & KADM5_LAST_SUCCESS) {
	krb5_ret_int32(sp, &tmp);
	princ->last_success = tmp;
    }
    if (mask & KADM5_LAST_FAILED) {
	krb5_ret_int32(sp, &tmp);
	princ->last_failed = tmp;
    }
    if (mask & KADM5_FAIL_AUTH_COUNT) {
	krb5_ret_int32(sp, &tmp);
	princ->fail_auth_count = tmp;
    }
    if (mask & KADM5_KEY_DATA) {
	krb5_ret_int32(sp, &tmp);
	princ->n_key_data = tmp;
	princ->key_data = malloc(princ->n_key_data * sizeof(*princ->key_data));
	if (princ->key_data == NULL && princ->n_key_data != 0)
	    return ENOMEM;
	for(i = 0; i < princ->n_key_data; i++)
	    kadm5_ret_key_data(sp, &princ->key_data[i]);
    }
    if (mask & KADM5_TL_DATA) {
	krb5_ret_int32(sp, &tmp);
	princ->n_tl_data = tmp;
	princ->tl_data = NULL;
	for(i = 0; i < princ->n_tl_data; i++){
	    krb5_tl_data *tp = malloc(sizeof(*tp));
	    if (tp == NULL)
		return ENOMEM;
	    kadm5_ret_tl_data(sp, tp);
	    tp->tl_data_next = princ->tl_data;
	    princ->tl_data = tp;
	}
    }
    return 0;
}