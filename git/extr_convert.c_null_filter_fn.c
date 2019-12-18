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
struct stream_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char const*,size_t) ; 

__attribute__((used)) static int null_filter_fn(struct stream_filter *filter,
			  const char *input, size_t *isize_p,
			  char *output, size_t *osize_p)
{
	size_t count;

	if (!input)
		return 0; /* we do not keep any states */
	count = *isize_p;
	if (*osize_p < count)
		count = *osize_p;
	if (count) {
		memmove(output, input, count);
		*isize_p -= count;
		*osize_p -= count;
	}
	return 0;
}