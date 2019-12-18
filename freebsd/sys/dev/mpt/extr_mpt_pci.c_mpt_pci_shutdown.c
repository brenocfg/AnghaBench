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
struct mpt_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int mpt_shutdown (struct mpt_softc*) ; 

__attribute__((used)) static int
mpt_pci_shutdown(device_t dev)
{
	struct mpt_softc *mpt;

	mpt = (struct mpt_softc *)device_get_softc(dev);
	if (mpt)
		return (mpt_shutdown(mpt));
	return(0);
}