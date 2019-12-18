#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dsgl_walk {int nents; TYPE_1__* to; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/ * addr; int /*<<< orphan*/ * len; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (size_t) ; 

__attribute__((used)) static inline void dsgl_walk_add_page(struct dsgl_walk *walk,
					size_t size,
					dma_addr_t addr)
{
	int j;

	if (!size)
		return;
	j = walk->nents;
	walk->to->len[j % 8] = htons(size);
	walk->to->addr[j % 8] = cpu_to_be64(addr);
	j++;
	if ((j % 8) == 0)
		walk->to++;
	walk->nents = j;
}