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
typedef  int /*<<< orphan*/  u32 ;
struct sec_dev_info {int dummy; } ;

/* Variables and functions */
 int SEC_MAX_SAA_NUM ; 
 int /*<<< orphan*/  sec_saa_getqm_en (struct sec_dev_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_saa_int_mask (struct sec_dev_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sec_hw_exit(struct sec_dev_info *info)
{
	int i;

	for (i = 0; i < SEC_MAX_SAA_NUM; i++) {
		sec_saa_int_mask(info, i, (u32)~0);
		sec_saa_getqm_en(info, i, 0);
	}
}