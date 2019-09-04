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
 int /*<<< orphan*/  sc25519_mul (unsigned char*,unsigned char const*,unsigned char const*) ; 

__attribute__((used)) static inline void
sc25519_sq(unsigned char *s, const unsigned char *a)
{
    sc25519_mul(s, a, a);
}