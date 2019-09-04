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
struct index_state {int dummy; } ;
struct diff_filespec {TYPE_1__* driver; } ;
struct TYPE_2__ {char const* word_regex; } ;

/* Variables and functions */
 int /*<<< orphan*/  diff_filespec_load_driver (struct diff_filespec*,struct index_state*) ; 

__attribute__((used)) static const char *userdiff_word_regex(struct diff_filespec *one,
				       struct index_state *istate)
{
	diff_filespec_load_driver(one, istate);
	return one->driver->word_regex;
}