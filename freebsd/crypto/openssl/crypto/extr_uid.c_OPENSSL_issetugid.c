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
 int /*<<< orphan*/  AT_SECURE ; 
 scalar_t__ getauxval (int /*<<< orphan*/ ) ; 
 scalar_t__ getegid () ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getgid () ; 
 scalar_t__ getuid () ; 

int OPENSSL_issetugid(void)
{
# ifdef OSSL_IMPLEMENT_GETAUXVAL
    return getauxval(AT_SECURE) != 0;
# else
    return getuid() != geteuid() || getgid() != getegid();
# endif
}