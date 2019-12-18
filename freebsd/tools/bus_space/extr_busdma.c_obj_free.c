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
struct obj {size_t oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct obj*) ; 
 int /*<<< orphan*/ ** oidtbl ; 

__attribute__((used)) static int
obj_free(struct obj *obj)
{

	oidtbl[obj->oid] = NULL;
	free(obj);
	return (0);
}