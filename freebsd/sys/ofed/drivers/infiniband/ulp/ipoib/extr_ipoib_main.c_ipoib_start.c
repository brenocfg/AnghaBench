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
struct ifnet {int /*<<< orphan*/  if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ipoib_start (struct ifnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipoib_start(struct ifnet *dev)
{
	_ipoib_start(dev, dev->if_softc);
}