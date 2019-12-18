#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {TYPE_1__* sym_out; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ventry; } ;
struct TYPE_5__ {int /*<<< orphan*/  st_value; } ;
typedef  TYPE_2__ SymLook ;
typedef  int /*<<< orphan*/  Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  SYMLOOK_EARLY ; 
 int /*<<< orphan*/  symlook_init (TYPE_2__*,char*) ; 
 int symlook_obj (TYPE_2__*,int /*<<< orphan*/ *) ; 

uint64_t
set_gp(Obj_Entry *obj)
{
	uint64_t old;
	SymLook req;
	uint64_t gp;
	int res;

	__asm __volatile("mv    %0, gp" : "=r"(old));

	symlook_init(&req, "__global_pointer$");
	req.ventry = NULL;
	req.flags = SYMLOOK_EARLY;
	res = symlook_obj(&req, obj);

	if (res == 0) {
		gp = req.sym_out->st_value;
		__asm __volatile("mv    gp, %0" :: "r"(gp));
	}

	return (old);
}