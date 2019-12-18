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
struct dbm_match {int dummy; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MACRO_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  page_bymacro (scalar_t__,struct dbm_match const*) ; 

void
dbm_page_bymacro(int32_t im, const struct dbm_match *match)
{
	assert(im >= 0);
	assert(im < MACRO_MAX);
	assert(match != NULL);
	page_bymacro(im, match);
}