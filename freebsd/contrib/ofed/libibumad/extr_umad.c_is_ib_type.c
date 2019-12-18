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
typedef  int /*<<< orphan*/  dir_name ;

/* Variables and functions */
 char* SYS_INFINIBAND ; 
 int /*<<< orphan*/  SYS_NODE_TYPE ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 scalar_t__ sys_read_uint (char*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned is_ib_type(const char *ca_name)
{
	char dir_name[256];
	unsigned type;

	snprintf(dir_name, sizeof(dir_name), "%s/%s", SYS_INFINIBAND, ca_name);

	if (sys_read_uint(dir_name, SYS_NODE_TYPE, &type) < 0)
		return 0;

	return type >= 1 && type <= 3 ? 1 : 0;
}