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
typedef  int /*<<< orphan*/ * rtbl_t ;
typedef  scalar_t__ gss_const_OID ;
struct TYPE_8__ {scalar_t__ value; scalar_t__ length; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  TYPE_2__* gss_OID_set ;
struct TYPE_9__ {size_t count; int /*<<< orphan*/ * elements; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  COL_DESC ; 
 int /*<<< orphan*/  COL_OID ; 
 int /*<<< orphan*/  COL_VALUE ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ gss_display_mech_attr (scalar_t__*,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ gss_mo_get (scalar_t__,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  rtbl_add_column (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_add_column_entryv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * rtbl_create () ; 
 int /*<<< orphan*/  rtbl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtbl_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_set_separator (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
print_mech_attr(const char *mechname, gss_const_OID mech, gss_OID_set set)
{
    gss_buffer_desc name, desc;
    OM_uint32 major, minor;
    rtbl_t ct;
    size_t n;

    ct = rtbl_create();
    if (ct == NULL)
	errx(1, "rtbl_create");

    rtbl_set_separator(ct, "  ");
    rtbl_add_column(ct, COL_OID, 0);
    rtbl_add_column(ct, COL_DESC, 0);
    if (mech)
	rtbl_add_column(ct, COL_VALUE, 0);

    for (n = 0; n < set->count; n++) {
	major = gss_display_mech_attr(&minor, &set->elements[n], &name, &desc, NULL);
	if (major)
	    continue;

	rtbl_add_column_entryv(ct, COL_OID, "%.*s",
			       (int)name.length, (char *)name.value);
	rtbl_add_column_entryv(ct, COL_DESC, "%.*s",
			       (int)desc.length, (char *)desc.value);
	if (mech) {
	    gss_buffer_desc value;

	    if (gss_mo_get(mech, &set->elements[n], &value) != 0)
		value.length = 0;

	    if (value.length)
		rtbl_add_column_entryv(ct, COL_VALUE, "%.*s",
				       (int)value.length, (char *)value.value);
	    else
		rtbl_add_column_entryv(ct, COL_VALUE, "<>");
	    gss_release_buffer(&minor, &value);
	}

	gss_release_buffer(&minor, &name);
	gss_release_buffer(&minor, &desc);
    }

    printf("attributes for: %s\n", mechname);
    rtbl_format(ct, stdout);
    rtbl_destroy(ct);
}