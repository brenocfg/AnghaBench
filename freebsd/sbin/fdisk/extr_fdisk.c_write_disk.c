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
typedef  scalar_t__ ssize_t ;
typedef  int off_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  fd ; 
 scalar_t__ geom_class_available (char*) ; 
 scalar_t__ pwrite (int /*<<< orphan*/ ,void*,scalar_t__,int) ; 
 scalar_t__ secsize ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
write_disk(off_t sector, void *buf)
{
	ssize_t wr;

	/*
	 * Try to write MBR directly. This may help when disk
	 * is not in use.
	 * XXX: hardcoded sectorsize
	 */
	wr = pwrite(fd, buf, secsize, (sector * 512));
	if (wr == secsize)
		return (0);

	if (geom_class_available("PART") != 0)
		warnx("Failed to write MBR. Try to use gpart(8).");
	else
		warnx("Failed to write sector zero");
	return(EINVAL);
}