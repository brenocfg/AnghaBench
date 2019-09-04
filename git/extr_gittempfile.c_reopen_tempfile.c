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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct tempfile {scalar_t__ fd; TYPE_1__ filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  is_tempfile_active (struct tempfile*) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int) ; 

int reopen_tempfile(struct tempfile *tempfile)
{
	if (!is_tempfile_active(tempfile))
		BUG("reopen_tempfile called for an inactive object");
	if (0 <= tempfile->fd)
		BUG("reopen_tempfile called for an open object");
	tempfile->fd = open(tempfile->filename.buf, O_WRONLY|O_TRUNC);
	return tempfile->fd;
}