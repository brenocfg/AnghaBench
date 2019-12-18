#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ucl_userdata_emitter ;
typedef  int /*<<< orphan*/  ucl_userdata_dtor ;
typedef  int /*<<< orphan*/  ucl_object_t ;
struct TYPE_3__ {void* ud; } ;
struct TYPE_4__ {int ref; TYPE_1__ value; int /*<<< orphan*/ * prev; int /*<<< orphan*/ * next; int /*<<< orphan*/  type; } ;
struct ucl_object_userdata {TYPE_2__ obj; int /*<<< orphan*/  emitter; int /*<<< orphan*/  dtor; } ;

/* Variables and functions */
 struct ucl_object_userdata* UCL_ALLOC (size_t) ; 
 int /*<<< orphan*/  UCL_USERDATA ; 
 int /*<<< orphan*/  memset (struct ucl_object_userdata*,int /*<<< orphan*/ ,size_t) ; 

ucl_object_t*
ucl_object_new_userdata (ucl_userdata_dtor dtor,
		ucl_userdata_emitter emitter,
		void *ptr)
{
	struct ucl_object_userdata *new;
	size_t nsize = sizeof (*new);

	new = UCL_ALLOC (nsize);
	if (new != NULL) {
		memset (new, 0, nsize);
		new->obj.ref = 1;
		new->obj.type = UCL_USERDATA;
		new->obj.next = NULL;
		new->obj.prev = (ucl_object_t *)new;
		new->dtor = dtor;
		new->emitter = emitter;
		new->obj.value.ud = ptr;
	}

	return (ucl_object_t *)new;
}