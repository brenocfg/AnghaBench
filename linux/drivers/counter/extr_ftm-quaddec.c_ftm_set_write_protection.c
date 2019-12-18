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
 int /*<<< orphan*/  FTM_FIELD_UPDATE (struct ftm_quaddec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FTM_FMS ; 
 int /*<<< orphan*/  FTM_FMS_WPEN ; 

__attribute__((used)) static void ftm_set_write_protection(struct ftm_quaddec *ftm)
{
	FTM_FIELD_UPDATE(ftm, FTM_FMS, FTM_FMS_WPEN, 1);
}