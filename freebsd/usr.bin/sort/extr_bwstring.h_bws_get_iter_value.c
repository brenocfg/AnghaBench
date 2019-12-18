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
typedef  unsigned char wchar_t ;
typedef  scalar_t__ bwstring_iterator ;

/* Variables and functions */
 int MB_CUR_MAX ; 

__attribute__((used)) static inline wchar_t
bws_get_iter_value(bwstring_iterator iter)
{

	if (MB_CUR_MAX == 1)
		return *((unsigned char *) iter);
	else
		return *((wchar_t*) iter);
}