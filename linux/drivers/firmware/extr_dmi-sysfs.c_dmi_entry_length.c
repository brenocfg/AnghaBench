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
struct dmi_header {int /*<<< orphan*/  length; } ;

/* Variables and functions */

__attribute__((used)) static size_t dmi_entry_length(const struct dmi_header *dh)
{
	const char *p = (const char *)dh;

	p += dh->length;

	while (p[0] || p[1])
		p++;

	return 2 + p - (const char *)dh;
}