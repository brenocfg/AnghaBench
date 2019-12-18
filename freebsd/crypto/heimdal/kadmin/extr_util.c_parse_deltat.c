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
typedef  int /*<<< orphan*/  krb5_deltat ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  print_time_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ str2deltat (char const*,int /*<<< orphan*/ *) ; 

int
parse_deltat (const char *resp, krb5_deltat *value, int *mask, int bit)
{
    krb5_deltat tmp;

    if (str2deltat(resp, &tmp) == 0) {
	*value = tmp;
	if (mask)
	    *mask |= bit;
	return 0;
    } else if(*resp == '?') {
	print_time_table (stderr);
    } else {
	fprintf (stderr, "Unable to parse time \"%s\"\n", resp);
    }
    return -1;
}