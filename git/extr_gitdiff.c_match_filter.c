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
struct diff_options {int dummy; } ;
struct diff_filepair {scalar_t__ status; scalar_t__ score; } ;

/* Variables and functions */
 scalar_t__ DIFF_STATUS_FILTER_BROKEN ; 
 scalar_t__ DIFF_STATUS_MODIFIED ; 
 scalar_t__ filter_bit_tst (scalar_t__,struct diff_options const*) ; 

__attribute__((used)) static int match_filter(const struct diff_options *options, const struct diff_filepair *p)
{
	return (((p->status == DIFF_STATUS_MODIFIED) &&
		 ((p->score &&
		   filter_bit_tst(DIFF_STATUS_FILTER_BROKEN, options)) ||
		  (!p->score &&
		   filter_bit_tst(DIFF_STATUS_MODIFIED, options)))) ||
		((p->status != DIFF_STATUS_MODIFIED) &&
		 filter_bit_tst(p->status, options)));
}