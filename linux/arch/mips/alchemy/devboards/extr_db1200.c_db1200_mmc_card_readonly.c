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
 int /*<<< orphan*/  BCSR_STATUS ; 
 int BCSR_STATUS_SD0WP ; 
 int bcsr_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db1200_mmc_card_readonly(void *mmc_host)
{
	return (bcsr_read(BCSR_STATUS) & BCSR_STATUS_SD0WP) ? 1 : 0;
}