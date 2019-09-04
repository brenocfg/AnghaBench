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
struct packed_git {int /*<<< orphan*/ * index_data; int /*<<< orphan*/  index_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 

void close_pack_index(struct packed_git *p)
{
	if (p->index_data) {
		munmap((void *)p->index_data, p->index_size);
		p->index_data = NULL;
	}
}