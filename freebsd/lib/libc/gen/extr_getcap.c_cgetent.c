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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int getent (char**,int /*<<< orphan*/ *,char**,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
cgetent(char **buf, char **db_array, const char *name)
{
	u_int dummy;

	return (getent(buf, &dummy, db_array, -1, name, 0, NULL));
}