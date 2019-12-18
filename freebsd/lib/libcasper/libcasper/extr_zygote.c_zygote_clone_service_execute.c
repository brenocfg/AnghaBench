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
 int /*<<< orphan*/  ZYGOTE_SERVICE_EXECUTE ; 
 int zygote_clone (int /*<<< orphan*/ ,int*,int*) ; 

int
zygote_clone_service_execute(int *chanfdp, int *procfdp)
{

	return (zygote_clone(ZYGOTE_SERVICE_EXECUTE, chanfdp, procfdp));
}