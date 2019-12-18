#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* objects; } ;
struct TYPE_5__ {TYPE_1__* odb; } ;
struct TYPE_4__ {char* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 TYPE_3__* the_repository ; 

char *get_object_directory(void)
{
	if (!the_repository->objects->odb)
		BUG("git environment hasn't been setup");
	return the_repository->objects->odb->path;
}