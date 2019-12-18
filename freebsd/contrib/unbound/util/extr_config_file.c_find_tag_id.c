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
struct config_file {int num_tags; int /*<<< orphan*/ * tagname; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
find_tag_id(struct config_file* cfg, const char* tag)
{
	int i;
	for(i=0; i<cfg->num_tags; i++) {
		if(strcmp(cfg->tagname[i], tag) == 0)
			return i;
	}
	return -1;
}