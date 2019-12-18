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
typedef  int /*<<< orphan*/  u64 ;
struct spu {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * masks; } ;
struct TYPE_4__ {TYPE_1__ cache; int /*<<< orphan*/  spe_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  lv1_set_spe_interrupt_mask (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* spu_pdata (struct spu*) ; 

__attribute__((used)) static void int_mask_set(struct spu *spu, int class, u64 mask)
{
	spu_pdata(spu)->cache.masks[class] = mask;
	lv1_set_spe_interrupt_mask(spu_pdata(spu)->spe_id, class,
		spu_pdata(spu)->cache.masks[class]);
}