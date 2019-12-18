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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MIIBUS_WRITEREG (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
miibus_writereg(device_t dev, int phy, int reg, int data)
{
	device_t		parent;

	parent = device_get_parent(dev);
	return (MIIBUS_WRITEREG(parent, phy, reg, data));
}