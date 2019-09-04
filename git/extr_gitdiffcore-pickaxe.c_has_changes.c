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
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  mmfile_t ;
typedef  int /*<<< orphan*/  kwset_t ;

/* Variables and functions */
 unsigned int contains (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int has_changes(mmfile_t *one, mmfile_t *two,
		       struct diff_options *o,
		       regex_t *regexp, kwset_t kws)
{
	unsigned int one_contains = one ? contains(one, regexp, kws) : 0;
	unsigned int two_contains = two ? contains(two, regexp, kws) : 0;
	return one_contains != two_contains;
}