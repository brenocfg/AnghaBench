#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int function_result; char const* desc; } ;

/* Variables and functions */
 int nitems (TYPE_1__*) ; 
 TYPE_1__* smp_error_table ; 

const char *
smp_error_desc(int function_result)
{
	int i;

	for (i = 0; i < nitems(smp_error_table); i++){
		if (function_result == smp_error_table[i].function_result)
			return (smp_error_table[i].desc);
	}
	return ("Reserved Function Result");
}