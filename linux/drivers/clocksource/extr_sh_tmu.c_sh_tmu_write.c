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
struct sh_tmu_channel {scalar_t__ base; TYPE_1__* tmu; } ;
struct TYPE_2__ {int model; int /*<<< orphan*/  mapbase; } ;

/* Variables and functions */
#define  SH_TMU 129 
#define  SH_TMU_SH3 128 
 int TCR ; 
 int TSTR ; 
 int /*<<< orphan*/  iowrite16 (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (unsigned long,scalar_t__) ; 
 void iowrite8 (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sh_tmu_write(struct sh_tmu_channel *ch, int reg_nr,
				unsigned long value)
{
	unsigned long offs;

	if (reg_nr == TSTR) {
		switch (ch->tmu->model) {
		case SH_TMU_SH3:
			return iowrite8(value, ch->tmu->mapbase + 2);
		case SH_TMU:
			return iowrite8(value, ch->tmu->mapbase + 4);
		}
	}

	offs = reg_nr << 2;

	if (reg_nr == TCR)
		iowrite16(value, ch->base + offs);
	else
		iowrite32(value, ch->base + offs);
}