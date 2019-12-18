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
struct object_directory {struct object_directory* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct object_directory*) ; 
 int /*<<< orphan*/  odb_clear_loose_cache (struct object_directory*) ; 

__attribute__((used)) static void free_object_directory(struct object_directory *odb)
{
	free(odb->path);
	odb_clear_loose_cache(odb);
	free(odb);
}