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
 int EAGAIN ; 
 int cci_init_status ; 
 int cci_probe () ; 
 int /*<<< orphan*/  cci_probing ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cci_init(void)
{
	if (cci_init_status != -EAGAIN)
		return cci_init_status;

	mutex_lock(&cci_probing);
	if (cci_init_status == -EAGAIN)
		cci_init_status = cci_probe();
	mutex_unlock(&cci_probing);
	return cci_init_status;
}