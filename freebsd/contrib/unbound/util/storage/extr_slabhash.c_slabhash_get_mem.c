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
struct slabhash {int size; int /*<<< orphan*/ * array; } ;
struct lruhash {int dummy; } ;

/* Variables and functions */
 scalar_t__ lruhash_get_mem (int /*<<< orphan*/ ) ; 

size_t slabhash_get_mem(struct slabhash* sl)
{	
	size_t i, total = sizeof(*sl);
	total += sizeof(struct lruhash*)*sl->size;
	for(i=0; i<sl->size; i++) {
		total += lruhash_get_mem(sl->array[i]);
	}
	return total;
}