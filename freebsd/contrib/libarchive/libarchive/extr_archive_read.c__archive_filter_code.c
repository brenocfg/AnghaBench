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
struct archive_read_filter {int code; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 struct archive_read_filter* get_filter (struct archive*,int) ; 

__attribute__((used)) static int
_archive_filter_code(struct archive *_a, int n)
{
	struct archive_read_filter *f = get_filter(_a, n);
	return f == NULL ? -1 : f->code;
}