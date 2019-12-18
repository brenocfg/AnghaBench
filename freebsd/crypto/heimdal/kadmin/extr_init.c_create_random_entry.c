#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  pwbuf ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  char krb5_keyblock ;
typedef  scalar_t__ kadm5_ret_t ;
struct TYPE_7__ {unsigned int max_life; unsigned int max_renewable_life; int attributes; int kvno; int /*<<< orphan*/  principal; } ;
typedef  TYPE_1__ kadm5_principal_ent_rec ;
typedef  int /*<<< orphan*/  ent ;

/* Variables and functions */
 int KADM5_ATTRIBUTES ; 
 int KADM5_KVNO ; 
 int KADM5_MAX_LIFE ; 
 int KADM5_MAX_RLIFE ; 
 int KADM5_PRINCIPAL ; 
 int KRB5_KDB_DISALLOW_ALL_TIX ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kadm5_create_principal (int /*<<< orphan*/ ,TYPE_1__*,int,char const*) ; 
 int /*<<< orphan*/  kadm5_free_principal_ent (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ kadm5_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ kadm5_modify_principal (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ kadm5_randkey_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int*) ; 
 int /*<<< orphan*/  kadm_handle ; 
 int /*<<< orphan*/  krb5_free_keyblock_contents (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  random_password (char*,int) ; 

__attribute__((used)) static kadm5_ret_t
create_random_entry(krb5_principal princ,
		    unsigned max_life,
		    unsigned max_rlife,
		    uint32_t attributes)
{
    kadm5_principal_ent_rec ent;
    kadm5_ret_t ret;
    int mask = 0;
    krb5_keyblock *keys;
    int n_keys, i;
    char *name;
    const char *password;
    char pwbuf[512];

    random_password(pwbuf, sizeof(pwbuf));
    password = pwbuf;

    ret = krb5_unparse_name(context, princ, &name);
    if (ret) {
	krb5_warn(context, ret, "failed to unparse principal name");
	return ret;
    }

    memset(&ent, 0, sizeof(ent));
    ent.principal = princ;
    mask |= KADM5_PRINCIPAL;
    if (max_life) {
	ent.max_life = max_life;
	mask |= KADM5_MAX_LIFE;
    }
    if (max_rlife) {
	ent.max_renewable_life = max_rlife;
	mask |= KADM5_MAX_RLIFE;
    }
    ent.attributes |= attributes | KRB5_KDB_DISALLOW_ALL_TIX;
    mask |= KADM5_ATTRIBUTES;

    /* Create the entry with a random password */
    ret = kadm5_create_principal(kadm_handle, &ent, mask, password);
    if(ret) {
	krb5_warn(context, ret, "create_random_entry(%s): randkey failed",
		  name);
	goto out;
    }

    /* Replace the string2key based keys with real random bytes */
    ret = kadm5_randkey_principal(kadm_handle, princ, &keys, &n_keys);
    if(ret) {
	krb5_warn(context, ret, "create_random_entry(%s): randkey failed",
		  name);
	goto out;
    }
    for(i = 0; i < n_keys; i++)
	krb5_free_keyblock_contents(context, &keys[i]);
    free(keys);
    ret = kadm5_get_principal(kadm_handle, princ, &ent,
			      KADM5_PRINCIPAL | KADM5_ATTRIBUTES);
    if(ret) {
	krb5_warn(context, ret, "create_random_entry(%s): "
		  "unable to get principal", name);
	goto out;
    }
    ent.attributes &= (~KRB5_KDB_DISALLOW_ALL_TIX);
    ent.kvno = 1;
    ret = kadm5_modify_principal(kadm_handle, &ent,
				 KADM5_ATTRIBUTES|KADM5_KVNO);
    kadm5_free_principal_ent (kadm_handle, &ent);
    if(ret) {
	krb5_warn(context, ret, "create_random_entry(%s): "
		  "unable to modify principal", name);
	goto out;
    }
 out:
    free(name);
    return ret;
}