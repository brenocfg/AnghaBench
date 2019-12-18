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
struct ohash_info {int /*<<< orphan*/  free; int /*<<< orphan*/  calloc; int /*<<< orphan*/  alloc; } ;
struct ohash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ohash_delete (struct ohash*) ; 
 int /*<<< orphan*/  ohash_init (struct ohash*,int,struct ohash_info*) ; 
 int /*<<< orphan*/  xcalloc ; 
 int /*<<< orphan*/  xfree ; 
 int /*<<< orphan*/  xmalloc ; 

int
main(void)
{
	struct ohash h;
	struct ohash_info i;
	i.alloc = xmalloc;
	i.calloc = xcalloc;
	i.free = xfree;
	ohash_init(&h, 2, &i);
	ohash_delete(&h);
	return 0;
}