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
typedef  int /*<<< orphan*/  uint32_t ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_INL (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inline
ahci_set(struct resource *m, bus_size_t off, uint32_t set)
{
	uint32_t val = ATA_INL(m, off);

	val |= set;
	ATA_OUTL(m, off, val);
}