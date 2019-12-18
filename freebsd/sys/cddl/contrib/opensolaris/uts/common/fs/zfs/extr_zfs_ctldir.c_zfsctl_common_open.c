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
struct vop_open_args {int a_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int FWRITE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfsctl_common_open(struct vop_open_args *ap)
{
	int flags = ap->a_mode;

	if (flags & FWRITE)
		return (SET_ERROR(EACCES));

	return (0);
}