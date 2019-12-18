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
struct packed_git {int dummy; } ;
struct pack_info {struct packed_git* p; } ;

/* Variables and functions */
 struct pack_info** info ; 
 int num_pack ; 
 int /*<<< orphan*/  pack_basename (struct packed_git*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct pack_info *find_pack_by_name(const char *name)
{
	int i;
	for (i = 0; i < num_pack; i++) {
		struct packed_git *p = info[i]->p;
		if (!strcmp(pack_basename(p), name))
			return info[i];
	}
	return NULL;
}