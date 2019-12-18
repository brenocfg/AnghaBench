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
struct archive_read_filter {struct archive_read_filter* upstream; } ;
struct archive_read {struct archive_read_filter* filter; } ;
struct archive {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
_archive_filter_count(struct archive *_a)
{
	struct archive_read *a = (struct archive_read *)_a;
	struct archive_read_filter *p = a->filter;
	int count = 0;
	while(p) {
		count++;
		p = p->upstream;
	}
	return count;
}