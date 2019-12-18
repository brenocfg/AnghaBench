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
struct TYPE_2__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_read {TYPE_1__ archive; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_FORMAT_RAR_V5 ; 

__attribute__((used)) static void init_header(struct archive_read* a) {
	a->archive.archive_format = ARCHIVE_FORMAT_RAR_V5;
	a->archive.archive_format_name = "RAR5";
}