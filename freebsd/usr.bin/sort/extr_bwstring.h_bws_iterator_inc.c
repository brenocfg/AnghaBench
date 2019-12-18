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
typedef  unsigned char* bwstring_iterator ;

/* Variables and functions */
 int MB_CUR_MAX ; 

__attribute__((used)) static inline bwstring_iterator
bws_iterator_inc(bwstring_iterator iter, size_t pos)
{

	if (MB_CUR_MAX == 1)
		return ((unsigned char *) iter) + pos;
	else
		return ((wchar_t*) iter) + pos;
}