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
struct diff_options {int filter; } ;

/* Variables and functions */
 int* filter_bit ; 

__attribute__((used)) static unsigned filter_bit_tst(char status, const struct diff_options *opt)
{
	return opt->filter & filter_bit[(int) status];
}