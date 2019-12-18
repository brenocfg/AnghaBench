#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * origin_path; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MAX ; 
 int rtld_dirname_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
obj_resolve_origin(Obj_Entry *obj)
{

	if (obj->origin_path != NULL)
		return (true);
	obj->origin_path = xmalloc(PATH_MAX);
	return (rtld_dirname_abs(obj->path, obj->origin_path) != -1);
}