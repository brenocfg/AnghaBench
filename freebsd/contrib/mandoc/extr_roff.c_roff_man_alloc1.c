#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  macroset; TYPE_2__* first; } ;
struct roff_man {TYPE_1__ meta; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACROSET_NONE ; 
 int /*<<< orphan*/  ROFFT_ROOT ; 
 TYPE_2__* mandoc_calloc (int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roff_state_reset (struct roff_man*) ; 

__attribute__((used)) static void
roff_man_alloc1(struct roff_man *man)
{
	memset(&man->meta, 0, sizeof(man->meta));
	man->meta.first = mandoc_calloc(1, sizeof(*man->meta.first));
	man->meta.first->type = ROFFT_ROOT;
	man->meta.macroset = MACROSET_NONE;
	roff_state_reset(man);
}