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
typedef  scalar_t__ uintmax_t ;
struct convtbl {double mul; double scale; } ;

/* Variables and functions */
 struct convtbl* get_tbl_ptr (scalar_t__ const,int const) ; 

double
convert(const uintmax_t size, const int scale)
{
	struct convtbl	*tp;

	tp = get_tbl_ptr(size, scale);
	return ((double)size * tp->mul / tp->scale);

}