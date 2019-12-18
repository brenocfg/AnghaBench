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
struct bucket {struct bucket* name; } ;

/* Variables and functions */
 size_t cache_size ; 
 int /*<<< orphan*/  free (struct bucket*) ; 

__attribute__((used)) static void
cleanup(void *private)
{
	size_t i;
	struct bucket *cache = (struct bucket *)private;

	for (i = 0; i < cache_size; i++)
		free(cache[i].name);
	free(cache);
}