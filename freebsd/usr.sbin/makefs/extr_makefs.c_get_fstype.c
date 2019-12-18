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
struct TYPE_4__ {int /*<<< orphan*/ * type; } ;
typedef  TYPE_1__ fstype_t ;

/* Variables and functions */
 TYPE_1__* fstypes ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static fstype_t *
get_fstype(const char *type)
{
	int i;
	
	for (i = 0; fstypes[i].type != NULL; i++)
		if (strcmp(fstypes[i].type, type) == 0)
			return (&fstypes[i]);
	return (NULL);
}