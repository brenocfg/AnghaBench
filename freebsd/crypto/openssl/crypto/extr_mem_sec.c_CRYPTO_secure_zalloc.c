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
 void* CRYPTO_secure_malloc (size_t,char const*,int) ; 
 void* CRYPTO_zalloc (size_t,char const*,int) ; 
 scalar_t__ secure_mem_initialized ; 

void *CRYPTO_secure_zalloc(size_t num, const char *file, int line)
{
#ifdef OPENSSL_SECURE_MEMORY
    if (secure_mem_initialized)
        /* CRYPTO_secure_malloc() zeroes allocations when it is implemented */
        return CRYPTO_secure_malloc(num, file, line);
#endif
    return CRYPTO_zalloc(num, file, line);
}