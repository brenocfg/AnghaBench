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

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ fsync_object_files ; 
 int /*<<< orphan*/  fsync_or_die (int,char*) ; 

__attribute__((used)) static void close_loose_object(int fd)
{
	if (fsync_object_files)
		fsync_or_die(fd, "loose object file");
	if (close(fd) != 0)
		die_errno(_("error when closing loose object file"));
}