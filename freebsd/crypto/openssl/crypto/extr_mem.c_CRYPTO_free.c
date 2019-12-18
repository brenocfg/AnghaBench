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
 int /*<<< orphan*/  CRYPTO_mem_debug_free (void*,int,char const*,int) ; 
 int /*<<< orphan*/  INCREMENT (int /*<<< orphan*/ ) ; 
 scalar_t__ call_malloc_debug ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  free_count ; 
 void free_impl (void*,char const*,int) ; 

void CRYPTO_free(void *str, const char *file, int line)
{
    INCREMENT(free_count);
    if (free_impl != NULL && free_impl != &CRYPTO_free) {
        free_impl(str, file, line);
        return;
    }

#ifndef OPENSSL_NO_CRYPTO_MDEBUG
    if (call_malloc_debug) {
        CRYPTO_mem_debug_free(str, 0, file, line);
        free(str);
        CRYPTO_mem_debug_free(str, 1, file, line);
    } else {
        free(str);
    }
#else
    free(str);
#endif
}