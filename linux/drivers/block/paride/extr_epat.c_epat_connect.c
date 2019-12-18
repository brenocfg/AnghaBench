#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; int /*<<< orphan*/  saved_r2; int /*<<< orphan*/  saved_r0; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  CPP (int) ; 
 int /*<<< orphan*/  WR (int,int) ; 
 scalar_t__ epatc8 ; 
 int /*<<< orphan*/  r0 () ; 
 int /*<<< orphan*/  r2 () ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void epat_connect ( PIA *pi )

{       pi->saved_r0 = r0();
        pi->saved_r2 = r2();

 	/* Initialize the chip */
	CPP(0);

	if (epatc8) {
		CPP(0x40);CPP(0xe0);
		w0(0);w2(1);w2(4);
		WR(0x8,0x12);WR(0xc,0x14);WR(0x12,0x10);
		WR(0xe,0xf);WR(0xf,4);
		/* WR(0xe,0xa);WR(0xf,4); */
		WR(0xe,0xd);WR(0xf,0);
		/* CPP(0x30); */
	}

        /* Connect to the chip */
	CPP(0xe0);
        w0(0);w2(1);w2(4); /* Idle into SPP */
        if (pi->mode >= 3) {
          w0(0);w2(1);w2(4);w2(0xc);
          /* Request EPP */
          w0(0x40);w2(6);w2(7);w2(4);w2(0xc);w2(4);
        }

	if (!epatc8) {
		WR(8,0x10); WR(0xc,0x14); WR(0xa,0x38); WR(0x12,0x10);
	}
}