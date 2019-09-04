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
 int /*<<< orphan*/  sodium_misuse () ; 

__attribute__((used)) static void
sodium_base64_check_variant(const int variant)
{
    if ((((unsigned int) variant) & ~ 0x6U) != 0x1U) {
        sodium_misuse();
    }
}