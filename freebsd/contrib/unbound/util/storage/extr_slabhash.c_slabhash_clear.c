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

/* Variables and functions */
 int /*<<< orphan*/  lruhash_clear (int /*<<< orphan*/ ) ; 

void slabhash_clear(struct slabhash* sl)
{
	size_t i;
	if(!sl)
		return;
	for(i=0; i<sl->size; i++)
		lruhash_clear(sl->array[i]);
}