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
struct qce_device {int dummy; } ;

/* Variables and functions */
 int CORE_MAJOR_REV_MASK ; 
 int CORE_MAJOR_REV_SHIFT ; 
 int CORE_MINOR_REV_MASK ; 
 int CORE_MINOR_REV_SHIFT ; 
 int CORE_STEP_REV_MASK ; 
 int CORE_STEP_REV_SHIFT ; 
 int /*<<< orphan*/  REG_VERSION ; 
 int qce_read (struct qce_device*,int /*<<< orphan*/ ) ; 

void qce_get_version(struct qce_device *qce, u32 *major, u32 *minor, u32 *step)
{
	u32 val;

	val = qce_read(qce, REG_VERSION);
	*major = (val & CORE_MAJOR_REV_MASK) >> CORE_MAJOR_REV_SHIFT;
	*minor = (val & CORE_MINOR_REV_MASK) >> CORE_MINOR_REV_SHIFT;
	*step = (val & CORE_STEP_REV_MASK) >> CORE_STEP_REV_SHIFT;
}