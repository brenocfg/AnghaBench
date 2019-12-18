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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int dsl_prop_get (char const*,char const*,int,int,int /*<<< orphan*/ *,char*) ; 

int
dsl_prop_get_integer(const char *ddname, const char *propname,
    uint64_t *valuep, char *setpoint)
{
	return (dsl_prop_get(ddname, propname, 8, 1, valuep, setpoint));
}