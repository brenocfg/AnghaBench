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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  irp ;

/* Variables and functions */
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoInitializeIrp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoSizeOfIrp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 

__attribute__((used)) static irp *
IoAllocateIrp(uint8_t stsize, uint8_t chargequota)
{
	irp			*i;

	i = ExAllocatePoolWithTag(NonPagedPool, IoSizeOfIrp(stsize), 0);
	if (i == NULL)
		return (NULL);

	IoInitializeIrp(i, IoSizeOfIrp(stsize), stsize);

	return (i);
}