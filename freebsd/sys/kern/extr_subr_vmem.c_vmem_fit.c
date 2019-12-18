#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vmem_size_t ;
typedef  int vmem_addr_t ;
struct TYPE_4__ {int bt_size; int bt_start; } ;
typedef  TYPE_1__ bt_t ;

/* Variables and functions */
 int BT_END (TYPE_1__ const*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int VMEM_ALIGNUP (int,int) ; 
 scalar_t__ VMEM_CROSS_P (int,int,int) ; 

__attribute__((used)) static int
vmem_fit(const bt_t *bt, vmem_size_t size, vmem_size_t align,
    vmem_size_t phase, vmem_size_t nocross, vmem_addr_t minaddr,
    vmem_addr_t maxaddr, vmem_addr_t *addrp)
{
	vmem_addr_t start;
	vmem_addr_t end;

	MPASS(size > 0);
	MPASS(bt->bt_size >= size); /* caller's responsibility */

	/*
	 * XXX assumption: vmem_addr_t and vmem_size_t are
	 * unsigned integer of the same size.
	 */

	start = bt->bt_start;
	if (start < minaddr) {
		start = minaddr;
	}
	end = BT_END(bt);
	if (end > maxaddr)
		end = maxaddr;
	if (start > end) 
		return (ENOMEM);

	start = VMEM_ALIGNUP(start - phase, align) + phase;
	if (start < bt->bt_start)
		start += align;
	if (VMEM_CROSS_P(start, start + size - 1, nocross)) {
		MPASS(align < nocross);
		start = VMEM_ALIGNUP(start - phase, nocross) + phase;
	}
	if (start <= end && end - start >= size - 1) {
		MPASS((start & (align - 1)) == phase);
		MPASS(!VMEM_CROSS_P(start, start + size - 1, nocross));
		MPASS(minaddr <= start);
		MPASS(maxaddr == 0 || start + size - 1 <= maxaddr);
		MPASS(bt->bt_start <= start);
		MPASS(BT_END(bt) - start >= size - 1);
		*addrp = start;

		return (0);
	}
	return (ENOMEM);
}