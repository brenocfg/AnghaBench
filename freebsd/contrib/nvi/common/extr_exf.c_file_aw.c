#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ep; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  F_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_MODIFIED ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  O_AUTOWRITE ; 
 scalar_t__ O_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_READONLY ; 
 int file_write (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

int
file_aw(
	SCR *sp,
	int flags)
{
	if (!F_ISSET(sp->ep, F_MODIFIED))
		return (0);
	if (!O_ISSET(sp, O_AUTOWRITE))
		return (0);

	/*
	 * !!!
	 * Historic 4BSD vi attempted to write the file if autowrite was set,
	 * regardless of the writeability of the file (as defined by the file
	 * readonly flag).  System V changed this as some point, not attempting
	 * autowrite if the file was readonly.  This feels like a bug fix to
	 * me (e.g. the principle of least surprise is violated if readonly is
	 * set and vi writes the file), so I'm compatible with System V.
	 */
	if (O_ISSET(sp, O_READONLY)) {
		msgq(sp, M_INFO,
		    "266|File readonly, modifications not auto-written");
		return (1);
	}
	return (file_write(sp, NULL, NULL, NULL, flags));
}