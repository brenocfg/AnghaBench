#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int alignment; int /*<<< orphan*/  taken_list; int /*<<< orphan*/  free_list; int /*<<< orphan*/  empty_list; scalar_t__ flags; scalar_t__ empty_slots; scalar_t__ max_blocks; int /*<<< orphan*/ * block; } ;
typedef  TYPE_1__ rh_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_1__* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 

rh_info_t *rh_create(unsigned int alignment)
{
	rh_info_t *info;

	/* Alignment must be a power of two */
	if ((alignment & (alignment - 1)) != 0)
		return ERR_PTR(-EINVAL);

	info = kmalloc(sizeof(*info), GFP_ATOMIC);
	if (info == NULL)
		return ERR_PTR(-ENOMEM);

	info->alignment = alignment;

	/* Initially everything as empty */
	info->block = NULL;
	info->max_blocks = 0;
	info->empty_slots = 0;
	info->flags = 0;

	INIT_LIST_HEAD(&info->empty_list);
	INIT_LIST_HEAD(&info->free_list);
	INIT_LIST_HEAD(&info->taken_list);

	return info;
}