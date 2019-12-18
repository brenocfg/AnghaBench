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
 int /*<<< orphan*/  DNSCRYPT_SHARED_SECRET_KEY_LENGTH ; 
 int sodium_memcmp (void*,void*,int /*<<< orphan*/ ) ; 

int
dnsc_shared_secrets_compfunc(void *m1, void *m2)
{
    return sodium_memcmp(m1, m2, DNSCRYPT_SHARED_SECRET_KEY_LENGTH);
}