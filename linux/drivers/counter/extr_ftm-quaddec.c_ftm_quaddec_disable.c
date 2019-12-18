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
struct ftm_quaddec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTM_MODE ; 
 int /*<<< orphan*/  FTM_QDCTRL ; 
 int /*<<< orphan*/  ftm_clear_write_protection (struct ftm_quaddec*) ; 
 int /*<<< orphan*/  ftm_set_write_protection (struct ftm_quaddec*) ; 
 int /*<<< orphan*/  ftm_write (struct ftm_quaddec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftm_quaddec_disable(void *ftm)
{
	struct ftm_quaddec *ftm_qua = ftm;

	ftm_clear_write_protection(ftm_qua);
	ftm_write(ftm_qua, FTM_MODE, 0);
	ftm_write(ftm_qua, FTM_QDCTRL, 0);
	/*
	 * This is enough to disable the counter. No clock has been
	 * selected by writing to FTM_SC in init()
	 */
	ftm_set_write_protection(ftm_qua);
}