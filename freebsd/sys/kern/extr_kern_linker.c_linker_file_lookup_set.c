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
typedef  int /*<<< orphan*/  linker_file_t ;

/* Variables and functions */
 int LINKER_LOOKUP_SET (int /*<<< orphan*/ ,char const*,void*,void*,int*) ; 
 int /*<<< orphan*/  SA_LOCKED ; 
 int /*<<< orphan*/  kld_sx ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
linker_file_lookup_set(linker_file_t file, const char *name,
    void *firstp, void *lastp, int *countp)
{

	sx_assert(&kld_sx, SA_LOCKED);
	return (LINKER_LOOKUP_SET(file, name, firstp, lastp, countp));
}