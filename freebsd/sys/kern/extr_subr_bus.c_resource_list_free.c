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
struct resource_list_entry {scalar_t__ res; } ;
struct resource_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BUS ; 
 struct resource_list_entry* STAILQ_FIRST (struct resource_list*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (struct resource_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct resource_list_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  panic (char*) ; 

void
resource_list_free(struct resource_list *rl)
{
	struct resource_list_entry *rle;

	while ((rle = STAILQ_FIRST(rl)) != NULL) {
		if (rle->res)
			panic("resource_list_free: resource entry is busy");
		STAILQ_REMOVE_HEAD(rl, link);
		free(rle, M_BUS);
	}
}