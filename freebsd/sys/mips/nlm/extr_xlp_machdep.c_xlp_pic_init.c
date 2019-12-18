#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct timecounter {unsigned int member_2; char* member_4; int member_5; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIC_CLOCK_TIMER ; 
 int /*<<< orphan*/  XLP_IO_CLK ; 
 int /*<<< orphan*/  XLP_PCI_DEVINFO_REG0 ; 
 int /*<<< orphan*/  nlm_get_pic_pcibase (int /*<<< orphan*/ ) ; 
 scalar_t__ nlm_get_pic_regbase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_nodeid () ; 
 int /*<<< orphan*/  nlm_pic_set_timer (scalar_t__,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_pic_write_irt (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int nlm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_timecount ; 
 struct timecounter* platform_timecounter ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xlp_pic_base ; 

__attribute__((used)) static void
xlp_pic_init(void)
{
	struct timecounter pic_timecounter = {
		platform_get_timecount, /* get_timecount */
		0,                      /* no poll_pps */
		~0U,                    /* counter_mask */
		XLP_IO_CLK,            /* frequency */
		"XLRPIC",               /* name */
		2000,                   /* quality (adjusted in code) */
	};
        int i;
	int maxirt;

	xlp_pic_base = nlm_get_pic_regbase(0);  /* TOOD: Add other nodes */
	maxirt = nlm_read_reg(nlm_get_pic_pcibase(nlm_nodeid()),
	    XLP_PCI_DEVINFO_REG0);
        printf("Initializing PIC...@%jx %d IRTs\n", (uintmax_t)xlp_pic_base,
	    maxirt);
	/* Bind all PIC irqs to cpu 0 */
        for (i = 0; i < maxirt; i++)
	    nlm_pic_write_irt(xlp_pic_base, i, 0, 0, 1, 0,
	    1, 0, 0x1);

	nlm_pic_set_timer(xlp_pic_base, PIC_CLOCK_TIMER, ~0ULL, 0, 0);
	platform_timecounter = &pic_timecounter;
}