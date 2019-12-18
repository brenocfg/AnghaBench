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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 char* bridge_if_find_name (scalar_t__) ; 
 int strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,scalar_t__) ; 

int
bridge_compare_sysidx(uint32_t i1, uint32_t i2)
{
	int c;
	const char *b1, *b2;

	if (i1 == i2)
		return (0);

	if ((b1 = bridge_if_find_name(i1)) == NULL) {
		syslog(LOG_ERR, "Bridge interface %d does not exist", i1);
		return (-2);
	}

	if ((b2 = bridge_if_find_name(i2)) == NULL) {
		syslog(LOG_ERR, "Bridge interface %d does not exist", i2);
		return (-2);
	}

	if ((c = strcmp(b1, b2)) < 0)
		return (-1);
	else if (c > 0)
		return (1);

	return (0);
}