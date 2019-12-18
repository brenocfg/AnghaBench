#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct object_directory {struct object_directory* next; } ;
typedef  int (* alt_odb_fn ) (struct object_directory*,void*) ;
struct TYPE_7__ {TYPE_2__* objects; } ;
struct TYPE_6__ {TYPE_1__* odb; } ;
struct TYPE_5__ {struct object_directory* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  prepare_alt_odb (TYPE_3__*) ; 
 TYPE_3__* the_repository ; 

int foreach_alt_odb(alt_odb_fn fn, void *cb)
{
	struct object_directory *ent;
	int r = 0;

	prepare_alt_odb(the_repository);
	for (ent = the_repository->objects->odb->next; ent; ent = ent->next) {
		r = fn(ent, cb);
		if (r)
			break;
	}
	return r;
}