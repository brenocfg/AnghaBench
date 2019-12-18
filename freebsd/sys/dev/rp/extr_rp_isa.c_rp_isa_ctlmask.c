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
typedef  int /*<<< orphan*/  CONTROLLER_t ;

/* Variables and functions */
 int /*<<< orphan*/  rp_controller ; 
 unsigned char sGetControllerIntStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned char
rp_isa_ctlmask(CONTROLLER_t *ctlp)
{
	return sGetControllerIntStatus(rp_controller,ctlp);
}