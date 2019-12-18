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
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  dry_run ; 
 int /*<<< orphan*/  free (void*) ; 
 void* get_data (unsigned long) ; 
 int /*<<< orphan*/  write_object (unsigned int,int,void*,unsigned long) ; 

__attribute__((used)) static void unpack_non_delta_entry(enum object_type type, unsigned long size,
				   unsigned nr)
{
	void *buf = get_data(size);

	if (!dry_run && buf)
		write_object(nr, type, buf, size);
	else
		free(buf);
}