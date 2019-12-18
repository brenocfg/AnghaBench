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
struct flash_layout {int /*<<< orphan*/ * id; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ *) ; 

struct flash_layout *find_layout(struct flash_layout *layouts, const char *id)
{
	struct flash_layout *ret;
	struct flash_layout *l;

	ret = NULL;
	for (l = layouts; l->id != NULL; l++){
		if (strcasecmp(id, l->id) == 0) {
			ret = l;
			break;
		}
	};

	return ret;
}