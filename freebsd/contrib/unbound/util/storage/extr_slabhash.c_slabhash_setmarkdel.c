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
struct slabhash {size_t size; int /*<<< orphan*/ * array; } ;
typedef  int /*<<< orphan*/  lruhash_markdelfunc_type ;

/* Variables and functions */
 int /*<<< orphan*/  lruhash_setmarkdel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void slabhash_setmarkdel(struct slabhash* sl, lruhash_markdelfunc_type md)
{
	size_t i;
	for(i=0; i<sl->size; i++) {
		lruhash_setmarkdel(sl->array[i], md);
	}
}