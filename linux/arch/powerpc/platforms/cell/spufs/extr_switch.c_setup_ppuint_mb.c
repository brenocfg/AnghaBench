#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  puint_mb_R; } ;
struct spu_state {TYPE_3__ priv2; TYPE_2__* lscsa; } ;
struct spu {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * slot; } ;
struct TYPE_5__ {TYPE_1__ ppuint_mb; } ;

/* Variables and functions */

__attribute__((used)) static inline void setup_ppuint_mb(struct spu_state *csa, struct spu *spu)
{
	/* Restore, Step 36:
	 *     Copy the CSA.PUINT_MB data into the LSCSA.
	 */
	csa->lscsa->ppuint_mb.slot[0] = csa->priv2.puint_mb_R;
}