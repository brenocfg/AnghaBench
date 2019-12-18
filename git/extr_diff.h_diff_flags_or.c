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
struct diff_flags {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void diff_flags_or(struct diff_flags *a,
				 const struct diff_flags *b)
{
	char *tmp_a = (char *)a;
	const char *tmp_b = (const char *)b;
	int i;

	for (i = 0; i < sizeof(struct diff_flags); i++)
		tmp_a[i] |= tmp_b[i];
}