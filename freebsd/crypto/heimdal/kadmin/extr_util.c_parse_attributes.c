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
typedef  int /*<<< orphan*/  krb5_flags ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  kdb_attrs ; 
 int /*<<< orphan*/  print_flags_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ str2attributes (char const*,int /*<<< orphan*/ *) ; 

int
parse_attributes (const char *resp, krb5_flags *attr, int *mask, int bit)
{
    krb5_flags tmp = *attr;

    if (str2attributes(resp, &tmp) == 0) {
	*attr = tmp;
	if (mask)
	    *mask |= bit;
	return 0;
    } else if(*resp == '?') {
	print_flags_table (kdb_attrs, stderr);
    } else {
	fprintf (stderr, "Unable to parse \"%s\"\n", resp);
    }
    return -1;
}