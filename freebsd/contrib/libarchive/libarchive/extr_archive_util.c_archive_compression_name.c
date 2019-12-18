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
struct archive {int dummy; } ;

/* Variables and functions */
 char const* archive_filter_name (struct archive*,int /*<<< orphan*/ ) ; 

const char *
archive_compression_name(struct archive *a)
{
	return archive_filter_name(a, 0);
}