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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMOPS_IDX ; 
 int /*<<< orphan*/  lio_toggle_bar1_swapmode (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_bar1_mem64 (struct octeon_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_bar1_mem8 (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lio_pci_fastwrite(struct octeon_device *oct, uint32_t offset,
		  uint8_t *hostbuf, uint32_t len)
{

	while ((len) && ((unsigned long)offset) & 7) {
		lio_write_bar1_mem8(oct, offset++, *(hostbuf++));
		len--;
	}

	lio_toggle_bar1_swapmode(oct, MEMOPS_IDX);

	while (len >= 8) {
		lio_write_bar1_mem64(oct, offset, *((uint64_t *)hostbuf));
		offset += 8;
		hostbuf += 8;
		len -= 8;
	}

	lio_toggle_bar1_swapmode(oct, MEMOPS_IDX);

	while (len--)
		lio_write_bar1_mem8(oct, offset++, *(hostbuf++));
}