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
 int /*<<< orphan*/  OPENSSL_free (void*) ; 
 int /*<<< orphan*/  OPENSSL_secure_clear_free (void*,size_t) ; 
 unsigned int PEM_FLAG_SECURE ; 

__attribute__((used)) static void pem_free(void *p, unsigned int flags, size_t num)
{
    if (flags & PEM_FLAG_SECURE)
        OPENSSL_secure_clear_free(p, num);
    else
        OPENSSL_free(p);
}