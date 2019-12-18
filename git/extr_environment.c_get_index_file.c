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
struct TYPE_2__ {char* index_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 TYPE_1__* the_repository ; 

char *get_index_file(void)
{
	if (!the_repository->index_file)
		BUG("git environment hasn't been setup");
	return the_repository->index_file;
}