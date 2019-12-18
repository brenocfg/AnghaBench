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
struct setlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (struct setlist*) ; 
 int /*<<< orphan*/  cpuset_freelist_add (struct setlist*,int) ; 

__attribute__((used)) static void
cpuset_freelist_init(struct setlist *list, int count)
{

	LIST_INIT(list);
	cpuset_freelist_add(list, count);
}