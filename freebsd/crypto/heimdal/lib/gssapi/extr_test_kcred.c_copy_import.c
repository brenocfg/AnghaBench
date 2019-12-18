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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  gss_name_t ;
typedef  scalar_t__ gss_cred_usage_t ;
typedef  int /*<<< orphan*/  gss_cred_id_t ;
typedef  int /*<<< orphan*/  gss_OID_set ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_C_BOTH ; 
 int /*<<< orphan*/  GSS_C_INDEFINITE ; 
 int /*<<< orphan*/  GSS_C_INITIATE ; 
 int /*<<< orphan*/  GSS_C_NO_NAME ; 
 int /*<<< orphan*/  GSS_C_NO_OID_SET ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ gss_acquire_cred (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_compare_name (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ gss_inquire_cred (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_krb5_copy_ccache (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gss_krb5_import_cred (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_cred (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_name (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gss_release_oid_set (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_cc_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_new_unique (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_cc_type_memory ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
copy_import(void)
{
    gss_cred_id_t cred1, cred2;
    OM_uint32 maj_stat, min_stat;
    gss_name_t name1, name2;
    OM_uint32 lifetime1, lifetime2;
    gss_cred_usage_t usage1, usage2;
    gss_OID_set mechs1, mechs2;
    krb5_ccache id;
    krb5_error_code ret;
    krb5_context context;
    int equal;

    maj_stat = gss_acquire_cred(&min_stat, GSS_C_NO_NAME, GSS_C_INDEFINITE,
				GSS_C_NO_OID_SET, GSS_C_INITIATE,
				&cred1, NULL, NULL);
    if (maj_stat != GSS_S_COMPLETE)
	errx(1, "gss_acquire_cred");

    maj_stat = gss_inquire_cred(&min_stat, cred1, &name1, &lifetime1,
				&usage1, &mechs1);
    if (maj_stat != GSS_S_COMPLETE)
	errx(1, "gss_inquire_cred");

    ret = krb5_init_context(&context);
    if (ret)
	errx(1, "krb5_init_context");

    ret = krb5_cc_new_unique(context, krb5_cc_type_memory, NULL, &id);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_new_unique");

    maj_stat = gss_krb5_copy_ccache(&min_stat, cred1, id);
    if (maj_stat != GSS_S_COMPLETE)
	errx(1, "gss_krb5_copy_ccache");

    maj_stat = gss_krb5_import_cred(&min_stat, id, NULL, NULL, &cred2);
    if (maj_stat != GSS_S_COMPLETE)
	errx(1, "gss_krb5_import_cred");

    maj_stat = gss_inquire_cred(&min_stat, cred2, &name2, &lifetime2,
				&usage2, &mechs2);
    if (maj_stat != GSS_S_COMPLETE)
	errx(1, "gss_inquire_cred 2");

    maj_stat = gss_compare_name(&min_stat, name1, name2, &equal);
    if (maj_stat != GSS_S_COMPLETE)
	errx(1, "gss_compare_name");
    if (!equal)
	errx(1, "names not equal");

    if (lifetime1 != lifetime2)
	errx(1, "lifetime not equal %lu != %lu",
	     (unsigned long)lifetime1, (unsigned long)lifetime2);

    if (usage1 != usage2) {
	/* as long any of them is both are everything it ok */
	if (usage1 != GSS_C_BOTH && usage2 != GSS_C_BOTH)
	    errx(1, "usages disjoined");
    }

    gss_release_name(&min_stat, &name2);
    gss_release_oid_set(&min_stat, &mechs2);

    maj_stat = gss_inquire_cred(&min_stat, cred2, &name2, &lifetime2,
				&usage2, &mechs2);
    if (maj_stat != GSS_S_COMPLETE)
	errx(1, "gss_inquire_cred");

    maj_stat = gss_compare_name(&min_stat, name1, name2, &equal);
    if (maj_stat != GSS_S_COMPLETE)
	errx(1, "gss_compare_name");
    if (!equal)
	errx(1, "names not equal");

    if (lifetime1 != lifetime2)
	errx(1, "lifetime not equal %lu != %lu",
	     (unsigned long)lifetime1, (unsigned long)lifetime2);

    gss_release_cred(&min_stat, &cred1);
    gss_release_cred(&min_stat, &cred2);

    gss_release_name(&min_stat, &name1);
    gss_release_name(&min_stat, &name2);

#if 0
    compare(mechs1, mechs2);
#endif

    gss_release_oid_set(&min_stat, &mechs1);
    gss_release_oid_set(&min_stat, &mechs2);

    krb5_cc_destroy(context, id);
    krb5_free_context(context);
}