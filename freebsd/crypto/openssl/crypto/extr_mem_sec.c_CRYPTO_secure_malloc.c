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
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 void* CRYPTO_malloc (size_t,char const*,int) ; 
 int /*<<< orphan*/  sec_malloc_lock ; 
 int /*<<< orphan*/  secure_mem_initialized ; 
 size_t secure_mem_used ; 
 size_t sh_actual_size (void*) ; 
 void* sh_malloc (size_t) ; 

void *CRYPTO_secure_malloc(size_t num, const char *file, int line)
{
#ifdef OPENSSL_SECURE_MEMORY
    void *ret;
    size_t actual_size;

    if (!secure_mem_initialized) {
        return CRYPTO_malloc(num, file, line);
    }
    CRYPTO_THREAD_write_lock(sec_malloc_lock);
    ret = sh_malloc(num);
    actual_size = ret ? sh_actual_size(ret) : 0;
    secure_mem_used += actual_size;
    CRYPTO_THREAD_unlock(sec_malloc_lock);
    return ret;
#else
    return CRYPTO_malloc(num, file, line);
#endif /* OPENSSL_SECURE_MEMORY */
}