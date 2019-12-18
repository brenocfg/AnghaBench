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
struct oidvalue {int dummy; } ;
struct oidname {int dummy; } ;
struct oidformat {int dummy; } ;
struct oiddescription {int dummy; } ;
struct oid {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 scalar_t__ oid_get_description (struct oid const*,struct oiddescription*) ; 
 int /*<<< orphan*/  oid_get_format (struct oid const*,struct oidformat*) ; 
 int /*<<< orphan*/  oid_get_name (struct oid const*,struct oidname*) ; 
 int /*<<< orphan*/  oid_get_value (struct oid const*,struct oidformat*,struct oidvalue*) ; 
 int /*<<< orphan*/  oiddescription_print (struct oiddescription*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidname_has_labels (struct oidname*) ; 
 int /*<<< orphan*/  oidname_print (struct oidname*,struct oidformat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidvalue_print (struct oidvalue*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
oid_print(const struct oid *o, struct oidname *on, bool print_description,
    FILE *fp)
{
	struct oidformat of;
	struct oidvalue ov;
	struct oiddescription od;

	if (!oid_get_format(o, &of) || !oid_get_value(o, &of, &ov))
		return;
	oid_get_name(o, on);

	/*
	 * Print the line with the description. Prometheus expects a
	 * single unique description for every metric, which cannot be
	 * guaranteed by sysctl if labels are present. Omit the
	 * description if labels are present.
	 */
	if (print_description && !oidname_has_labels(on) &&
	    oid_get_description(o, &od)) {
		fprintf(fp, "# HELP ");
		oidname_print(on, &of, fp);
		fputc(' ', fp);
		oiddescription_print(&od, fp);
		fputc('\n', fp);
	}

	/* Print the line with the value. */
	oidname_print(on, &of, fp);
	fputc(' ', fp);
	oidvalue_print(&ov, fp);
	fputc('\n', fp);
}