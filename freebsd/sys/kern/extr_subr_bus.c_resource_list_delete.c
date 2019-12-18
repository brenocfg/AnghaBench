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
struct resource_list_entry {int /*<<< orphan*/ * res; } ;
struct resource_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BUS ; 
 int /*<<< orphan*/  STAILQ_REMOVE (struct resource_list*,struct resource_list_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct resource_list_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  resource_list_entry ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int,int) ; 

void
resource_list_delete(struct resource_list *rl, int type, int rid)
{
	struct resource_list_entry *rle = resource_list_find(rl, type, rid);

	if (rle) {
		if (rle->res != NULL)
			panic("resource_list_delete: resource has not been released");
		STAILQ_REMOVE(rl, rle, resource_list_entry, link);
		free(rle, M_BUS);
	}
}