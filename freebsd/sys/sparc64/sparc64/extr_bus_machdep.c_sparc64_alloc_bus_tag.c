#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bus_space_tag {int dummy; } ;
typedef  TYPE_1__* bus_space_tag_t ;
struct TYPE_4__ {int bst_type; void* bst_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bus_space_tag_t
sparc64_alloc_bus_tag(void *cookie, int type)
{
	bus_space_tag_t bt;

	bt = malloc(sizeof(struct bus_space_tag), M_DEVBUF, M_NOWAIT);
	if (bt == NULL)
		return (NULL);
	bt->bst_cookie = cookie;
	bt->bst_type = type;
	return (bt);
}