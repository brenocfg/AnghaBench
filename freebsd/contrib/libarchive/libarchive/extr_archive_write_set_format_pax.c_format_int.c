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
typedef  int uint64_t ;
typedef  int int64_t ;
typedef  scalar_t__ INT64_MAX ;

/* Variables and functions */
 int INT64_MIN ; 

__attribute__((used)) static char *
format_int(char *t, int64_t i)
{
	uint64_t ui;

	if (i < 0) 
		ui = (i == INT64_MIN) ? (uint64_t)(INT64_MAX) + 1 : (uint64_t)(-i);
	else
		ui = i;

	do {
		*--t = "0123456789"[ui % 10];
	} while (ui /= 10);
	if (i < 0)
		*--t = '-';
	return (t);
}