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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  krb5_timestamp ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ str2time_t (char const*,int /*<<< orphan*/ *) ; 

int
parse_timet (const char *resp, krb5_timestamp *value, int *mask, int bit)
{
    time_t tmp;

    if (str2time_t(resp, &tmp) == 0) {
	*value = tmp;
	if(mask)
	    *mask |= bit;
	return 0;
    }
    if(*resp != '?')
	fprintf (stderr, "Unable to parse time \"%s\"\n", resp);
    fprintf (stderr, "Print date on format YYYY-mm-dd [hh:mm:ss]\n");
    return -1;
}