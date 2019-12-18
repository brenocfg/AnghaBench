#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct init_options {scalar_t__ bare_flag; int /*<<< orphan*/ * realm_max_renewable_life_string; int /*<<< orphan*/ * realm_max_ticket_life_string; } ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int krb5_deltat ;
typedef  scalar_t__ kadm5_ret_t ;
struct TYPE_8__ {int max_life; int max_renewable_life; int /*<<< orphan*/  principal; int /*<<< orphan*/  attributes; } ;
typedef  TYPE_1__ kadm5_principal_ent_rec ;
typedef  int /*<<< orphan*/  ent ;
struct TYPE_9__ {int /*<<< orphan*/  (* hdb_close ) (int /*<<< orphan*/ ,TYPE_2__*) ;scalar_t__ (* hdb_open ) (int /*<<< orphan*/ ,TYPE_2__*,int,int) ;} ;
typedef  TYPE_2__ HDB ;

/* Variables and functions */
 int KADM5_ATTRIBUTES ; 
 int KADM5_MAX_LIFE ; 
 int KADM5_MAX_RLIFE ; 
 int KADM5_PRINCIPAL ; 
 int /*<<< orphan*/  KRB5_ANON_NAME ; 
 int /*<<< orphan*/  KRB5_KDB_DISALLOW_ALL_TIX ; 
 int KRB5_KDB_DISALLOW_POSTDATED ; 
 int KRB5_KDB_DISALLOW_PROXIABLE ; 
 int KRB5_KDB_DISALLOW_RENEWABLE ; 
 int KRB5_KDB_DISALLOW_TGT_BASED ; 
 int KRB5_KDB_PWCHANGE_SERVICE ; 
 int KRB5_KDB_REQUIRES_PRE_AUTH ; 
 int /*<<< orphan*/  KRB5_TGS_NAME ; 
 int /*<<< orphan*/  KRB5_WELLKNOWN_NAME ; 
 int O_CREAT ; 
 int O_RDWR ; 
 TYPE_2__* _kadm5_s_get_db (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  create_random_entry (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ edit_deltat (char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kadm5_create_principal (int /*<<< orphan*/ ,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  kadm_handle ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char*,char const*,...) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  local_flag ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ str2deltat (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_2__*) ; 

int
init(struct init_options *opt, int argc, char **argv)
{
    kadm5_ret_t ret;
    int i;
    HDB *db;
    krb5_deltat max_life = 0, max_rlife = 0;

    if (!local_flag) {
	krb5_warnx(context, "init is only available in local (-l) mode");
	return 0;
    }

    if (opt->realm_max_ticket_life_string) {
	if (str2deltat (opt->realm_max_ticket_life_string, &max_life) != 0) {
	    krb5_warnx (context, "unable to parse \"%s\"",
			opt->realm_max_ticket_life_string);
	    return 0;
	}
    }
    if (opt->realm_max_renewable_life_string) {
	if (str2deltat (opt->realm_max_renewable_life_string, &max_rlife) != 0) {
	    krb5_warnx (context, "unable to parse \"%s\"",
			opt->realm_max_renewable_life_string);
	    return 0;
	}
    }

    db = _kadm5_s_get_db(kadm_handle);

    ret = db->hdb_open(context, db, O_RDWR | O_CREAT, 0600);
    if(ret){
	krb5_warn(context, ret, "hdb_open");
	return 0;
    }
    db->hdb_close(context, db);
    for(i = 0; i < argc; i++){
	krb5_principal princ;
	const char *realm = argv[i];

	if (opt->realm_max_ticket_life_string == NULL) {
	    max_life = 0;
	    if(edit_deltat ("Realm max ticket life", &max_life, NULL, 0)) {
		return 0;
	    }
	}
	if (opt->realm_max_renewable_life_string == NULL) {
	    max_rlife = 0;
	    if(edit_deltat("Realm max renewable ticket life", &max_rlife,
			   NULL, 0)) {
		return 0;
	    }
	}

	/* Create `krbtgt/REALM' */
	ret = krb5_make_principal(context, &princ, realm,
				  KRB5_TGS_NAME, realm, NULL);
	if(ret)
	    return 0;

	create_random_entry(princ, max_life, max_rlife, 0);
	krb5_free_principal(context, princ);

	if (opt->bare_flag)
	    continue;

	/* Create `kadmin/changepw' */
	krb5_make_principal(context, &princ, realm,
			    "kadmin", "changepw", NULL);
	/*
	 * The Windows XP (at least) password changing protocol
	 * request the `kadmin/changepw' ticket with `renewable_ok,
	 * renewable, forwardable' and so fails if we disallow
	 * forwardable here.
	 */
	create_random_entry(princ, 5*60, 5*60,
			    KRB5_KDB_DISALLOW_TGT_BASED|
			    KRB5_KDB_PWCHANGE_SERVICE|
			    KRB5_KDB_DISALLOW_POSTDATED|
			    KRB5_KDB_DISALLOW_RENEWABLE|
			    KRB5_KDB_DISALLOW_PROXIABLE|
			    KRB5_KDB_REQUIRES_PRE_AUTH);
	krb5_free_principal(context, princ);

	/* Create `kadmin/admin' */
	krb5_make_principal(context, &princ, realm,
			    "kadmin", "admin", NULL);
	create_random_entry(princ, 60*60, 60*60, KRB5_KDB_REQUIRES_PRE_AUTH);
	krb5_free_principal(context, princ);

	/* Create `changepw/kerberos' (for v4 compat) */
	krb5_make_principal(context, &princ, realm,
			    "changepw", "kerberos", NULL);
	create_random_entry(princ, 60*60, 60*60,
			    KRB5_KDB_DISALLOW_TGT_BASED|
			    KRB5_KDB_PWCHANGE_SERVICE);

	krb5_free_principal(context, princ);

	/* Create `kadmin/hprop' for database propagation */
	krb5_make_principal(context, &princ, realm,
			    "kadmin", "hprop", NULL);
	create_random_entry(princ, 60*60, 60*60,
			    KRB5_KDB_REQUIRES_PRE_AUTH|
			    KRB5_KDB_DISALLOW_TGT_BASED);
	krb5_free_principal(context, princ);

	/* Create `WELLKNOWN/ANONYMOUS' for anonymous as-req */
	krb5_make_principal(context, &princ, realm,
			    KRB5_WELLKNOWN_NAME, KRB5_ANON_NAME, NULL);
	create_random_entry(princ, 60*60, 60*60,
			    KRB5_KDB_REQUIRES_PRE_AUTH);
	krb5_free_principal(context, princ);


	/* Create `default' */
	{
	    kadm5_principal_ent_rec ent;
	    int mask = 0;

	    memset (&ent, 0, sizeof(ent));
	    mask |= KADM5_PRINCIPAL;
	    krb5_make_principal(context, &ent.principal, realm,
				"default", NULL);
	    mask |= KADM5_MAX_LIFE;
	    ent.max_life = 24 * 60 * 60;
	    mask |= KADM5_MAX_RLIFE;
	    ent.max_renewable_life = 7 * ent.max_life;
	    ent.attributes = KRB5_KDB_DISALLOW_ALL_TIX;
	    mask |= KADM5_ATTRIBUTES;

	    ret = kadm5_create_principal(kadm_handle, &ent, mask, "");
	    if (ret)
		krb5_err (context, 1, ret, "kadm5_create_principal");

	    krb5_free_principal(context, ent.principal);
	}
    }
    return 0;
}