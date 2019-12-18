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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  Argon2_i ; 
 int argon2_hash (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,void const*,size_t const,void const*,size_t const,int /*<<< orphan*/ *,size_t const,char*,size_t const,int /*<<< orphan*/ ) ; 

int
argon2i_hash_encoded(const uint32_t t_cost, const uint32_t m_cost,
                     const uint32_t parallelism, const void *pwd,
                     const size_t pwdlen, const void *salt,
                     const size_t saltlen, const size_t hashlen, char *encoded,
                     const size_t encodedlen)
{
    return argon2_hash(t_cost, m_cost, parallelism, pwd, pwdlen, salt, saltlen,
                       NULL, hashlen, encoded, encodedlen, Argon2_i);
}