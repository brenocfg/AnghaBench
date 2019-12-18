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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int sodium_library_minimal () ; 
 scalar_t__ sodium_library_version_major () ; 
 scalar_t__ sodium_library_version_minor () ; 
 int /*<<< orphan*/ * sodium_version_string () ; 

int
main(void)
{
    printf("%d\n", sodium_version_string() != NULL);
    printf("%d\n", sodium_library_version_major() > 0);
    printf("%d\n", sodium_library_version_minor() >= 0);
#ifdef SODIUM_LIBRARY_MINIMAL
    assert(sodium_library_minimal() == 1);
#else
    assert(sodium_library_minimal() == 0);
#endif

    return 0;
}