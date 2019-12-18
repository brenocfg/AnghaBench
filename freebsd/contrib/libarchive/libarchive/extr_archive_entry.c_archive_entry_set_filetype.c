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
struct TYPE_2__ {unsigned int mode; } ;
struct archive_entry {TYPE_1__ acl; scalar_t__ stat_valid; } ;

/* Variables and functions */
 unsigned int AE_IFMT ; 

void
archive_entry_set_filetype(struct archive_entry *entry, unsigned int type)
{
	entry->stat_valid = 0;
	entry->acl.mode &= ~AE_IFMT;
	entry->acl.mode |= AE_IFMT & type;
}