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
struct archive_write {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 

__attribute__((used)) static int
_warc_close(struct archive_write *a)
{
	(void)a; /* UNUSED */
	return (ARCHIVE_OK);
}