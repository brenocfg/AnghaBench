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
typedef  size_t uint32_t ;
struct multi_pack_index {int fd; size_t num_packs; TYPE_1__** pack_names; TYPE_1__** packs; int /*<<< orphan*/  data_len; scalar_t__ data; } ;
struct TYPE_2__ {scalar_t__ multi_pack_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (TYPE_1__**) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  munmap (unsigned char*,int /*<<< orphan*/ ) ; 

void close_midx(struct multi_pack_index *m)
{
	uint32_t i;

	if (!m)
		return;

	munmap((unsigned char *)m->data, m->data_len);
	close(m->fd);
	m->fd = -1;

	for (i = 0; i < m->num_packs; i++) {
		if (m->packs[i])
			m->packs[i]->multi_pack_index = 0;
	}
	FREE_AND_NULL(m->packs);
	FREE_AND_NULL(m->pack_names);
}