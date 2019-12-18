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
struct attrs_for_mech_options {char* mech_string; scalar_t__ all_flag; } ;
typedef  int /*<<< orphan*/ * gss_OID_set ;
typedef  int /*<<< orphan*/ * gss_OID ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/ * GSS_C_NO_OID ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ gss_inquire_attrs_for_mech (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * gss_name_to_oid (char*) ; 
 int /*<<< orphan*/  gss_release_oid_set (scalar_t__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  print_mech_attr (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
attrs_for_mech(struct attrs_for_mech_options *opt, int argc, char **argv)
{
    gss_OID_set mech_attr = NULL, known_mech_attrs = NULL;
    gss_OID mech = GSS_C_NO_OID;
    OM_uint32 major, minor;

    if (opt->mech_string) {
	mech = gss_name_to_oid(opt->mech_string);
	if (mech == NULL)
	    errx(1, "mech %s is unknown", opt->mech_string);
    }

    major = gss_inquire_attrs_for_mech(&minor, mech, &mech_attr, &known_mech_attrs);
    if (major)
	errx(1, "gss_inquire_attrs_for_mech");

    if (mech) {
	print_mech_attr(opt->mech_string, mech, mech_attr);
    }

    if (opt->all_flag) {
	print_mech_attr("all mechs", NULL, known_mech_attrs);
    }

    gss_release_oid_set(&minor, &mech_attr);
    gss_release_oid_set(&minor, &known_mech_attrs);

    return 0;
}