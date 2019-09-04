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
 int /*<<< orphan*/  Argon2_i ; 
 int argon2_verify (char const*,void const*,size_t const,int /*<<< orphan*/ ) ; 

int
argon2i_verify(const char *encoded, const void *pwd, const size_t pwdlen)
{
    return argon2_verify(encoded, pwd, pwdlen, Argon2_i);
}