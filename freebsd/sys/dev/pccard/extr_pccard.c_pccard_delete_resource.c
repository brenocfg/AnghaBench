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
struct resource_list {int dummy; } ;
struct pccard_ivar {struct resource_list resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pccard_ivar* PCCARD_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_delete (struct resource_list*,int,int) ; 

__attribute__((used)) static void
pccard_delete_resource(device_t dev, device_t child, int type, int rid)
{
	struct pccard_ivar *devi = PCCARD_IVAR(child);
	struct resource_list *rl = &devi->resources;
	resource_list_delete(rl, type, rid);
}