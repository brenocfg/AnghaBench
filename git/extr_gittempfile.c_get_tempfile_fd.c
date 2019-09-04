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
struct tempfile {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  is_tempfile_active (struct tempfile*) ; 

int get_tempfile_fd(struct tempfile *tempfile)
{
	if (!is_tempfile_active(tempfile))
		BUG("get_tempfile_fd() called for inactive object");
	return tempfile->fd;
}