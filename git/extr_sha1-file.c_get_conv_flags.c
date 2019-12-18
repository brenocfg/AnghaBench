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
 int CONV_EOL_RENORMALIZE ; 
 int CONV_WRITE_OBJECT ; 
 unsigned int HASH_RENORMALIZE ; 
 unsigned int HASH_WRITE_OBJECT ; 
 int global_conv_flags_eol ; 

__attribute__((used)) static int get_conv_flags(unsigned flags)
{
	if (flags & HASH_RENORMALIZE)
		return CONV_EOL_RENORMALIZE;
	else if (flags & HASH_WRITE_OBJECT)
		return global_conv_flags_eol | CONV_WRITE_OBJECT;
	else
		return 0;
}