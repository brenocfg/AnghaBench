#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct image_params {TYPE_1__* args; } ;
typedef  int /*<<< orphan*/  register_t ;
struct TYPE_2__ {int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 int suword32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aout_fixup(register_t **stack_base, struct image_params *imgp)
{

	*(char **)stack_base -= sizeof(uint32_t);
	return (suword32(*stack_base, imgp->args->argc));
}