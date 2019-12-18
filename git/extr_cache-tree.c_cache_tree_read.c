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
struct cache_tree {int dummy; } ;

/* Variables and functions */
 struct cache_tree* read_one (char const**,unsigned long*) ; 

struct cache_tree *cache_tree_read(const char *buffer, unsigned long size)
{
	if (buffer[0])
		return NULL; /* not the whole tree */
	return read_one(&buffer, &size);
}