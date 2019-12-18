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
struct archive_read_disk {int dummy; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 

__attribute__((used)) static int
setup_sparse(struct archive_read_disk *a,
    struct archive_entry *entry, int *fd)
{
	(void)a;     /* UNUSED */
	(void)entry; /* UNUSED */
	(void)fd;    /* UNUSED */
	return (ARCHIVE_OK);
}