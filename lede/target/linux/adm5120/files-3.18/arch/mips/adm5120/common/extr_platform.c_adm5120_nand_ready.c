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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int ADM5120_NAND_STATUS_READY ; 
 int adm5120_nand_get_status () ; 

__attribute__((used)) static int adm5120_nand_ready(struct mtd_info *mtd)
{
	return ((adm5120_nand_get_status() & ADM5120_NAND_STATUS_READY) != 0);
}