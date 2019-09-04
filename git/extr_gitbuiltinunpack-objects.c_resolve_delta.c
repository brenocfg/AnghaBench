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
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* patch_delta (void*,unsigned long,void*,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  write_object (unsigned int,int,void*,unsigned long) ; 

__attribute__((used)) static void resolve_delta(unsigned nr, enum object_type type,
			  void *base, unsigned long base_size,
			  void *delta, unsigned long delta_size)
{
	void *result;
	unsigned long result_size;

	result = patch_delta(base, base_size,
			     delta, delta_size,
			     &result_size);
	if (!result)
		die("failed to apply delta");
	free(delta);
	write_object(nr, type, result, result_size);
}