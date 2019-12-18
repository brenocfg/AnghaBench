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
typedef  int u64 ;

/* Variables and functions */
 int EINVAL ; 
 int RTAS_FADUMP_GPR_MASK ; 
 int fadump_str_to_u64 (char*) ; 
 scalar_t__ kstrtoint (char*,int,int*) ; 

__attribute__((used)) static inline int rtas_fadump_gpr_index(u64 id)
{
	char str[3];
	int i = -1;

	if ((id & RTAS_FADUMP_GPR_MASK) == fadump_str_to_u64("GPR")) {
		/* get the digits at the end */
		id &= ~RTAS_FADUMP_GPR_MASK;
		id >>= 24;
		str[2] = '\0';
		str[1] = id & 0xff;
		str[0] = (id >> 8) & 0xff;
		if (kstrtoint(str, 10, &i))
			i = -EINVAL;
		if (i > 31)
			i = -1;
	}
	return i;
}