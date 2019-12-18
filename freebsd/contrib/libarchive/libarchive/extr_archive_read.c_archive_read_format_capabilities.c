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
struct archive_read {TYPE_1__* format; } ;
struct archive {int dummy; } ;
struct TYPE_2__ {int (* format_capabilties ) (struct archive_read*) ;} ;

/* Variables and functions */
 int ARCHIVE_READ_FORMAT_CAPS_NONE ; 
 int stub1 (struct archive_read*) ; 

int
archive_read_format_capabilities(struct archive *_a)
{
	struct archive_read *a = (struct archive_read *)_a;
	if (a && a->format && a->format->format_capabilties) {
		return (a->format->format_capabilties)(a);
	}
	return ARCHIVE_READ_FORMAT_CAPS_NONE;
}