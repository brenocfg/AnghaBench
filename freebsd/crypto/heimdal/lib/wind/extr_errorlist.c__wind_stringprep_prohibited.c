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
typedef  int /*<<< orphan*/  wind_profile_flags ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ _wind_stringprep_error (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

int
_wind_stringprep_prohibited(const uint32_t *in, size_t in_len,
			    wind_profile_flags flags)
{
    unsigned i;

    for (i = 0; i < in_len; ++i)
	if (_wind_stringprep_error(in[i], flags))
	    return 1;
    return 0;
}