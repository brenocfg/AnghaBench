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
 scalar_t__ OPENSSL_issetugid () ; 
 char* getenv (char const*) ; 
 char* secure_getenv (char const*) ; 

char *ossl_safe_getenv(const char *name)
{
#if defined(__GLIBC__) && defined(__GLIBC_PREREQ)
# if __GLIBC_PREREQ(2, 17)
#  define SECURE_GETENV
    return secure_getenv(name);
# endif
#endif

#ifndef SECURE_GETENV
    if (OPENSSL_issetugid())
        return NULL;
    return getenv(name);
#endif
}