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
struct viapm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SMBHCTRL ; 
 int /*<<< orphan*/  SMBHCTRL_KILL ; 
 int /*<<< orphan*/  VIAPM_OUTB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
viapm_abort(struct viapm_softc *viapm)
{
	VIAPM_OUTB(SMBHCTRL, SMBHCTRL_KILL);
	DELAY(10);

	return (0);
}