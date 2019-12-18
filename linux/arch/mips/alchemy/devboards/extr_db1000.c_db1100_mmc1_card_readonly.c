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

/* Variables and functions */
 int /*<<< orphan*/  BCSR_BOARD ; 
 int BCSR_BOARD_SD1WP ; 
 int bcsr_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db1100_mmc1_card_readonly(void *mmc_host)
{
	return (bcsr_read(BCSR_BOARD) & BCSR_BOARD_SD1WP) ? 1 : 0;
}