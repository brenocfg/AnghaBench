#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* buffer; } ;
typedef  TYPE_1__ git_odb_object ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (void*) ; 

void git_odb_object__free(void *object)
{
	if (object != NULL) {
		git__free(((git_odb_object *)object)->buffer);
		git__free(object);
	}
}