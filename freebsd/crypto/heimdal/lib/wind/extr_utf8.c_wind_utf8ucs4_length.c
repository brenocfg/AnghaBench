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
 int wind_utf8ucs4 (char const*,int /*<<< orphan*/ *,size_t*) ; 

int
wind_utf8ucs4_length(const char *in, size_t *out_len)
{
    return wind_utf8ucs4(in, NULL, out_len);
}