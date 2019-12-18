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
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb_free (struct adapter*) ; 
 struct adapter* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cxgb_controller_detach(device_t dev)
{
	struct adapter *sc;

	sc = device_get_softc(dev);

	cxgb_free(sc);

	return (0);
}