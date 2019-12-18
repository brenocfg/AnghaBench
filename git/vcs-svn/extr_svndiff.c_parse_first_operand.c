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
 unsigned char OPERAND_MASK ; 
 int parse_int (char const**,size_t*,char const*) ; 

__attribute__((used)) static int parse_first_operand(const char **buf, size_t *out, const char *end)
{
	size_t result = (unsigned char) *(*buf)++ & OPERAND_MASK;
	if (result) {	/* immediate operand */
		*out = result;
		return 0;
	}
	return parse_int(buf, out, end);
}