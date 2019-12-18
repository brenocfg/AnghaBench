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
struct ib_gid_attr {int /*<<< orphan*/  gid_type; } ;

/* Variables and functions */
 char* ib_cache_gid_type_str (int /*<<< orphan*/ ) ; 
 size_t sprintf (char*,char*,char*) ; 

__attribute__((used)) static size_t print_gid_type(struct ib_gid_attr *gid_attr, char *buf)
{
	return sprintf(buf, "%s\n", ib_cache_gid_type_str(gid_attr->gid_type));
}