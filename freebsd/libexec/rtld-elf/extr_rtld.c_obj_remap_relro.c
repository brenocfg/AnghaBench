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
struct TYPE_3__ {scalar_t__ relro_size; int /*<<< orphan*/  path; int /*<<< orphan*/  relro_page; } ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  _rtld_error (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int mprotect (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  rtld_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
obj_remap_relro(Obj_Entry *obj, int prot)
{

	if (obj->relro_size > 0 && mprotect(obj->relro_page, obj->relro_size,
	    prot) == -1) {
		_rtld_error("%s: Cannot set relro protection to %#x: %s",
		    obj->path, prot, rtld_strerror(errno));
		return (-1);
	}
	return (0);
}