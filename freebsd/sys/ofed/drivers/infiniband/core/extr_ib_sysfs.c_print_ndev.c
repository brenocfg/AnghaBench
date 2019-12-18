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
struct ib_gid_attr {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 size_t EINVAL ; 
 char* if_name (int /*<<< orphan*/ ) ; 
 size_t sprintf (char*,char*,char*) ; 

__attribute__((used)) static size_t print_ndev(struct ib_gid_attr *gid_attr, char *buf)
{
	if (!gid_attr->ndev)
		return -EINVAL;

	return sprintf(buf, "%s\n", if_name(gid_attr->ndev));
}