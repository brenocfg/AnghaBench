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
struct error_entry {scalar_t__ start; scalar_t__ len; } ;

/* Variables and functions */

__attribute__((used)) static int
error_entry_cmp(const void *a, const void *b)
{
    const struct error_entry *ea = (const struct error_entry*)a;
    const struct error_entry *eb = (const struct error_entry*)b;

    if (ea->start >= eb->start && ea->start < eb->start + eb->len)
	return 0;
    return ea->start - eb->start;
}