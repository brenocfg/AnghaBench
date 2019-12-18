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
typedef  size_t __u8 ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const* const*) ; 

__attribute__((used)) static const char *sense_key_string(__u8 index)
{
	static const char * const info[] = {
		"No sense", "Recovered error", "Not ready",
		"Medium error", "Hardware error", "Illegal request",
		"Unit attention", "Data protect", "Blank check",
	};

	return index < ARRAY_SIZE(info) ? info[index] : "INVALID";
}