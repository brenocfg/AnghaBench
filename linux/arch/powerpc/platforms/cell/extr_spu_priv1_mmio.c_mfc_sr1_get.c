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
typedef  int /*<<< orphan*/  u64 ;
struct spu {TYPE_1__* priv1; } ;
struct TYPE_2__ {int /*<<< orphan*/  mfc_sr1_RW; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_be64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 mfc_sr1_get(struct spu *spu)
{
	return in_be64(&spu->priv1->mfc_sr1_RW);
}