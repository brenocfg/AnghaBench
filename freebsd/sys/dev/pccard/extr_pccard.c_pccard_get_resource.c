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
struct resource_list_entry {int /*<<< orphan*/  count; int /*<<< orphan*/  start; } ;
struct resource_list {int dummy; } ;
struct pccard_ivar {struct resource_list resources; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 struct pccard_ivar* PCCARD_IVAR (int /*<<< orphan*/ ) ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int,int) ; 

__attribute__((used)) static int
pccard_get_resource(device_t dev, device_t child, int type, int rid,
    rman_res_t *startp, rman_res_t *countp)
{
	struct pccard_ivar *devi = PCCARD_IVAR(child);
	struct resource_list *rl = &devi->resources;
	struct resource_list_entry *rle;

	rle = resource_list_find(rl, type, rid);
	if (rle == NULL)
		return (ENOENT);

	if (startp != NULL)
		*startp = rle->start;
	if (countp != NULL)
		*countp = rle->count;

	return (0);
}