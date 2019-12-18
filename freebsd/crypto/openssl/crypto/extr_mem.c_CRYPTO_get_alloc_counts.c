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
 int /*<<< orphan*/  free_count ; 
 int /*<<< orphan*/  malloc_count ; 
 int /*<<< orphan*/  realloc_count ; 
 int tsan_load (int /*<<< orphan*/ *) ; 

void CRYPTO_get_alloc_counts(int *mcount, int *rcount, int *fcount)
{
    if (mcount != NULL)
        *mcount = tsan_load(&malloc_count);
    if (rcount != NULL)
        *rcount = tsan_load(&realloc_count);
    if (fcount != NULL)
        *fcount = tsan_load(&free_count);
}