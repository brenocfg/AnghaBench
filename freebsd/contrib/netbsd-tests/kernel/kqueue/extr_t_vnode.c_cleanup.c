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
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_inside1 ; 
 int /*<<< orphan*/  dir_inside2 ; 
 int /*<<< orphan*/  dir_outside ; 
 int /*<<< orphan*/  dir_target ; 
 int /*<<< orphan*/  file_inside1 ; 
 int /*<<< orphan*/  file_inside2 ; 
 int /*<<< orphan*/  file_outside ; 
 int /*<<< orphan*/  kq ; 
 int /*<<< orphan*/  rmdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void
cleanup(void)
{
	(void)unlink(file_inside1);
	(void)unlink(file_inside2);
	(void)unlink(file_outside);
	(void)rmdir(dir_inside1);
	(void)rmdir(dir_inside2);
	(void)rmdir(dir_outside);
	(void)rmdir(dir_target);
	(void)close(kq);
	(void)close(target);
}