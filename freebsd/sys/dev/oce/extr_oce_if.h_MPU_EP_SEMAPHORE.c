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
typedef  int /*<<< orphan*/  POCE_SOFTC ;

/* Variables and functions */
 scalar_t__ IS_BE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_SH (int /*<<< orphan*/ ) ; 
 int MPU_EP_SEMAPHORE_BE3 ; 
 int MPU_EP_SEMAPHORE_SH ; 
 int MPU_EP_SEMAPHORE_XE201 ; 

__attribute__((used)) static inline int MPU_EP_SEMAPHORE(POCE_SOFTC sc)
{
	if (IS_BE(sc))
		return MPU_EP_SEMAPHORE_BE3;
	else if (IS_SH(sc))
		return MPU_EP_SEMAPHORE_SH;
	else
		return MPU_EP_SEMAPHORE_XE201;
}