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
struct bitmap {unsigned char* map; } ;

/* Variables and functions */
 int /*<<< orphan*/  bm_getmask (int*,unsigned char*) ; 

int
bm_isset(struct bitmap * bm, int pos)
{
	unsigned char   bmask;

	bm_getmask(&pos, &bmask);
	return !!(bm->map[pos] & bmask);
}