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
struct TYPE_2__ {int mode; } ;
struct archive_entry {TYPE_1__ acl; } ;
typedef  int mode_t ;

/* Variables and functions */
 int AE_IFMT ; 

mode_t
archive_entry_filetype(struct archive_entry *entry)
{
	return (AE_IFMT & entry->acl.mode);
}