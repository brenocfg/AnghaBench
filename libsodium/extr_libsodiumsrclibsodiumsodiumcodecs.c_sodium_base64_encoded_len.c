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
 size_t sodium_base64_ENCODED_LEN (size_t const,int const) ; 
 int /*<<< orphan*/  sodium_base64_check_variant (int const) ; 

size_t
sodium_base64_encoded_len(const size_t bin_len, const int variant)
{
    sodium_base64_check_variant(variant);

    return sodium_base64_ENCODED_LEN(bin_len, variant);
}