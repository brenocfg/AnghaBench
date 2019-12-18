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
struct bios_regs {int eax; scalar_t__ edx; scalar_t__ ecx; scalar_t__ ebx; } ;
struct TYPE_2__ {int id; } ;
struct bios32_SDentry {scalar_t__ entry; scalar_t__ base; int /*<<< orphan*/  ventry; scalar_t__ len; TYPE_1__ ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIOS_PADDRTOVADDR (scalar_t__) ; 
 int /*<<< orphan*/  GCODE_SEL ; 
 int /*<<< orphan*/  GSEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEL_KPL ; 
 int /*<<< orphan*/  bios32 (struct bios_regs*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bios32_SDCI ; 

int
bios32_SDlookup(struct bios32_SDentry *ent)
{
    struct bios_regs args;

    if (bios32_SDCI == 0)
	return (1);

    args.eax = ent->ident.id;		/* set up arguments */
    args.ebx = args.ecx = args.edx = 0;
    bios32(&args, bios32_SDCI, GSEL(GCODE_SEL, SEL_KPL));
    if ((args.eax & 0xff) == 0) {	/* success? */
	ent->base = args.ebx;
	ent->len = args.ecx;
	ent->entry = args.edx;
	ent->ventry = BIOS_PADDRTOVADDR(ent->base + ent->entry);
	return (0);			/* all OK */
    }
    return (1);				/* failed */
}