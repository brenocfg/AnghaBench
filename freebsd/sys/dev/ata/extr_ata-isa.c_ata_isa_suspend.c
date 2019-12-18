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
struct ata_channel {int /*<<< orphan*/  attached; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ata_suspend (int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_isa_suspend(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);

    if (!ch->attached)
	return (0);

    return ata_suspend(dev);
}