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
struct bts_phys {unsigned long offset; scalar_t__ size; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bts_buffer_pad_out(struct bts_phys *phys, unsigned long head)
{
	unsigned long index = head - phys->offset;

	memset(page_address(phys->page) + index, 0, phys->size - index);
}