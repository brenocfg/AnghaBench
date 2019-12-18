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
typedef  int uintmax_t ;
struct convtbl {int dummy; } ;

/* Variables and functions */
 int MEGABYTE ; 
 int const SC_AUTO ; 
 int SC_BIT ; 
 int SC_KILOBYTE ; 
 struct convtbl* convtbl ; 

__attribute__((used)) static
struct convtbl *
get_tbl_ptr(const uintmax_t size, const int scale)
{
	uintmax_t	 tmp;
	int		 idx;

	/* If our index is out of range, default to auto-scaling. */
	idx = scale < SC_AUTO ? scale : SC_AUTO;

	if (idx == SC_AUTO)
		/*
		 * Simple but elegant algorithm.  Count how many times
		 * we can shift our size value right by a factor of ten,
		 * incrementing an index each time.  We then use the
		 * index as the array index into the conversion table.
		 */
		for (tmp = size, idx = SC_KILOBYTE;
		     tmp >= MEGABYTE && idx < SC_BIT - 1;
		     tmp >>= 10, idx++);

	return (&convtbl[idx]);
}