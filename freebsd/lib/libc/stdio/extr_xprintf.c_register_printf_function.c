#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  printf_function ;
typedef  int /*<<< orphan*/  printf_arginfo_function ;
struct TYPE_2__ {int /*<<< orphan*/ * arginfo; int /*<<< orphan*/ * gnurender; } ;

/* Variables and functions */
 int __use_xprintf ; 
 TYPE_1__* printf_tbl ; 

int
register_printf_function(int spec, printf_function *render, printf_arginfo_function *arginfo)
{

	if (spec > 255 || spec < 0)
		return (-1);
	printf_tbl[spec].gnurender = render;
	printf_tbl[spec].arginfo = arginfo;
	__use_xprintf = 1;
	return (0);
}