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
typedef  scalar_t__ u_int ;
struct obj {scalar_t__ refcnt; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENXIO ; 
 scalar_t__ OBJ_TYPE_NONE ; 
 int /*<<< orphan*/  errno ; 
 int noids ; 
 struct obj** oidtbl ; 

__attribute__((used)) static struct obj *
obj_lookup(int oid, u_int type)
{
	struct obj *obj;

	if (oid < 0 || oid >= noids) {
		errno = EINVAL;
		return (NULL);
	}
	obj = oidtbl[oid];
	if (obj->refcnt == 0) {
		errno = ENXIO;
		return (NULL);
	}
	if (type != OBJ_TYPE_NONE && obj->type != type) {
		errno = ENODEV;
		return (NULL);
	}
	return (obj);
}