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
struct zip {scalar_t__ unconsumed; } ;
struct archive_read {TYPE_1__* format; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 

__attribute__((used)) static int
archive_read_format_zip_read_data_skip_seekable(struct archive_read *a)
{
	struct zip *zip;
	zip = (struct zip *)(a->format->data);

	zip->unconsumed = 0;
	return (ARCHIVE_OK);
}