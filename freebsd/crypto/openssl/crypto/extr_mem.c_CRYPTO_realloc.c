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
 int /*<<< orphan*/  CRYPTO_free (void*,char const*,int) ; 
 void* CRYPTO_malloc (size_t,char const*,int) ; 
 int /*<<< orphan*/  CRYPTO_mem_debug_realloc (void*,void*,size_t,int,char const*,int) ; 
 int /*<<< orphan*/  FAILTEST () ; 
 int /*<<< orphan*/  INCREMENT (int /*<<< orphan*/ ) ; 
 scalar_t__ call_malloc_debug ; 
 void* realloc (void*,size_t) ; 
 int /*<<< orphan*/  realloc_count ; 
 void* realloc_impl (void*,size_t,char const*,int) ; 

void *CRYPTO_realloc(void *str, size_t num, const char *file, int line)
{
    INCREMENT(realloc_count);
    if (realloc_impl != NULL && realloc_impl != &CRYPTO_realloc)
        return realloc_impl(str, num, file, line);

    FAILTEST();
    if (str == NULL)
        return CRYPTO_malloc(num, file, line);

    if (num == 0) {
        CRYPTO_free(str, file, line);
        return NULL;
    }

#ifndef OPENSSL_NO_CRYPTO_MDEBUG
    if (call_malloc_debug) {
        void *ret;
        CRYPTO_mem_debug_realloc(str, NULL, num, 0, file, line);
        ret = realloc(str, num);
        CRYPTO_mem_debug_realloc(str, ret, num, 1, file, line);
        return ret;
    }
#else
    (void)(file); (void)(line);
#endif
    return realloc(str, num);

}