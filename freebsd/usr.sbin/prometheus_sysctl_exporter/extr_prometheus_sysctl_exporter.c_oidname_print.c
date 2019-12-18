#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t len; } ;
struct oidname {char* names; char* labels; TYPE_1__ oid; } ;
struct oidformat {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char const,int /*<<< orphan*/ *) ; 
 scalar_t__ isalnum (char const) ; 
 scalar_t__ oidformat_is_temperature (struct oidformat const*) ; 
 scalar_t__ oidformat_is_timeval (struct oidformat const*) ; 
 scalar_t__ strlen (char const*) ; 
 size_t strspn (char const*,char*) ; 

__attribute__((used)) static void
oidname_print(const struct oidname *on, const struct oidformat *of,
    FILE *fp)
{
	const char *name, *label;
	size_t i;
	char separator;

	/* Print the name of the metric. */
	fprintf(fp, "sysctl");
	name = on->names;
	label = on->labels;
	for (i = 0; i < on->oid.len; ++i) {
		if (*label == '\0') {
			fputc('_', fp);
			while (*name != '\0') {
				/* Map unsupported characters to underscores. */
				fputc(isalnum(*name) ? *name : '_', fp);
				++name;
			}
		}
		name += strlen(name) + 1;
		label += strlen(label) + 1;
	}
	if (oidformat_is_temperature(of))
		fprintf(fp, "_celcius");
	else if (oidformat_is_timeval(of))
		fprintf(fp, "_seconds");

	/* Print the labels of the metric. */
	name = on->names;
	label = on->labels;
	separator = '{';
	for (i = 0; i < on->oid.len; ++i) {
		if (*label != '\0') {
			assert(label[strspn(label,
			    "abcdefghijklmnopqrstuvwxyz"
			    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			    "0123456789_")] == '\0');
			fprintf(fp, "%c%s=\"", separator, label);
			while (*name != '\0') {
				/* Escape backslashes and double quotes. */
				if (*name == '\\' || *name == '"')
					fputc('\\', fp);
				fputc(*name++, fp);
			}
			fputc('"', fp);
			separator = ',';
		}
		name += strlen(name) + 1;
		label += strlen(label) + 1;
	}
	if (separator != '{')
		fputc('}', fp);
}