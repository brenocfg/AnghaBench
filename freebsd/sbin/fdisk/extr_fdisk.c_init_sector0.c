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
struct dos_partition {unsigned long dp_start; scalar_t__ dp_size; int /*<<< orphan*/  dp_flag; int /*<<< orphan*/  dp_typ; } ;
struct TYPE_2__ {struct dos_partition* parts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVE ; 
 int /*<<< orphan*/  DOSPTYP_386BSD ; 
 int /*<<< orphan*/  disksecs ; 
 int /*<<< orphan*/  dos (struct dos_partition*) ; 
 int /*<<< orphan*/  dos_cylsecs ; 
 unsigned long dos_sectors ; 
 int /*<<< orphan*/  init_boot () ; 
 TYPE_1__ mboot ; 
 scalar_t__ rounddown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long roundup (unsigned long,unsigned long) ; 

__attribute__((used)) static void
init_sector0(unsigned long start)
{
	struct dos_partition *partp = &mboot.parts[0];

	init_boot();

	partp->dp_typ = DOSPTYP_386BSD;
	partp->dp_flag = ACTIVE;
	start = roundup(start, dos_sectors);
	if(start == 0)
		start = dos_sectors;
	partp->dp_start = start;
	partp->dp_size = rounddown(disksecs, dos_cylsecs) - start;

	dos(partp);
}