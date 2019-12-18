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
struct iso9660 {unsigned char* wbuff; int wbuff_remaining; } ;
struct archive_write {scalar_t__ format_data; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned char *
wb_buffptr(struct archive_write *a)
{
	struct iso9660 *iso9660 = (struct iso9660 *)a->format_data;

	return (&(iso9660->wbuff[sizeof(iso9660->wbuff)
		- iso9660->wbuff_remaining]));
}