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
typedef  int uint16_t ;
struct ns_result_str {int res; char const* str; } ;

/* Variables and functions */
 struct ns_result_str* ns_result ; 

__attribute__((used)) static const char *
get_res_str(uint16_t res)
{
	struct ns_result_str *t = ns_result;

	while (t->res != 0xFFFF) {
		if (t->res == res)
			return (t->str);
		t++;
	}
	return t->str;
}