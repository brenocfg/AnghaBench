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
struct pack_info {int old_num; } ;

/* Variables and functions */
 struct pack_info* find_pack_by_name (char const*) ; 

__attribute__((used)) static int parse_pack_def(const char *packname, int old_cnt)
{
	struct pack_info *i = find_pack_by_name(packname);
	if (i) {
		i->old_num = old_cnt;
		return 0;
	}
	else {
		/* The file describes a pack that is no longer here */
		return 1;
	}
}