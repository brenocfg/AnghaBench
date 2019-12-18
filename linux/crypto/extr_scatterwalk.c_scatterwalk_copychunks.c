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
typedef  int /*<<< orphan*/  u8 ;
struct scatter_walk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_dir (void*,int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  scatterwalk_advance (struct scatter_walk*,unsigned int) ; 
 int /*<<< orphan*/ * scatterwalk_map (struct scatter_walk*) ; 
 int /*<<< orphan*/  scatterwalk_pagedone (struct scatter_walk*,int,int) ; 
 unsigned int scatterwalk_pagelen (struct scatter_walk*) ; 
 int /*<<< orphan*/  scatterwalk_unmap (int /*<<< orphan*/ *) ; 

void scatterwalk_copychunks(void *buf, struct scatter_walk *walk,
			    size_t nbytes, int out)
{
	for (;;) {
		unsigned int len_this_page = scatterwalk_pagelen(walk);
		u8 *vaddr;

		if (len_this_page > nbytes)
			len_this_page = nbytes;

		if (out != 2) {
			vaddr = scatterwalk_map(walk);
			memcpy_dir(buf, vaddr, len_this_page, out);
			scatterwalk_unmap(vaddr);
		}

		scatterwalk_advance(walk, len_this_page);

		if (nbytes == len_this_page)
			break;

		buf += len_this_page;
		nbytes -= len_this_page;

		scatterwalk_pagedone(walk, out & 1, 1);
	}
}