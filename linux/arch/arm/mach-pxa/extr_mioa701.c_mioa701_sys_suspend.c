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
typedef  int u32 ;

/* Variables and functions */
 int BOOTSTRAP_WORDS ; 
 int /*<<< orphan*/  GPIO83_BT_ON ; 
 int /*<<< orphan*/  MFP_LPM_DRIVE_HIGH ; 
 int /*<<< orphan*/  MFP_LPM_DRIVE_LOW ; 
 int /*<<< orphan*/  RESUME_BT_ADDR ; 
 int /*<<< orphan*/  RESUME_ENABLE_ADDR ; 
 int RESUME_ENABLE_VAL ; 
 int /*<<< orphan*/  RESUME_UNKNOWN_ADDR ; 
 int /*<<< orphan*/  RESUME_VECTOR_ADDR ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  install_bootstrap () ; 
 int* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa2xx_mfp_set_lpm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* save_buffer ; 

__attribute__((used)) static int mioa701_sys_suspend(void)
{
	int i = 0, is_bt_on;
	u32 *mem_resume_vector	= phys_to_virt(RESUME_VECTOR_ADDR);
	u32 *mem_resume_enabler = phys_to_virt(RESUME_ENABLE_ADDR);
	u32 *mem_resume_bt	= phys_to_virt(RESUME_BT_ADDR);
	u32 *mem_resume_unknown	= phys_to_virt(RESUME_UNKNOWN_ADDR);

	/* Devices prepare suspend */
	is_bt_on = !!gpio_get_value(GPIO83_BT_ON);
	pxa2xx_mfp_set_lpm(GPIO83_BT_ON,
			   is_bt_on ? MFP_LPM_DRIVE_HIGH : MFP_LPM_DRIVE_LOW);

	for (i = 0; i < BOOTSTRAP_WORDS; i++)
		save_buffer[i] = mem_resume_vector[i];
	save_buffer[i++] = *mem_resume_enabler;
	save_buffer[i++] = *mem_resume_bt;
	save_buffer[i++] = *mem_resume_unknown;

	*mem_resume_enabler = RESUME_ENABLE_VAL;
	*mem_resume_bt	    = is_bt_on;

	install_bootstrap();
	return 0;
}