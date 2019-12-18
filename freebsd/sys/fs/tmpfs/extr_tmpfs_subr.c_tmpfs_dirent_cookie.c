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
struct tmpfs_dirent {scalar_t__ td_cookie; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ TMPFS_DIRCOOKIE_EOF ; 
 scalar_t__ TMPFS_DIRCOOKIE_MIN ; 

__attribute__((used)) static __inline off_t
tmpfs_dirent_cookie(struct tmpfs_dirent *de)
{
	if (de == NULL)
		return (TMPFS_DIRCOOKIE_EOF);

	MPASS(de->td_cookie >= TMPFS_DIRCOOKIE_MIN);

	return (de->td_cookie);
}