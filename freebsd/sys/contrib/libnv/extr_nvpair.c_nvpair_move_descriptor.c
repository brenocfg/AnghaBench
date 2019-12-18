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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  ERRNO_RESTORE () ; 
 int /*<<< orphan*/  ERRNO_SAVE () ; 
 int /*<<< orphan*/  ERRNO_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_TYPE_DESCRIPTOR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fd_is_valid (int) ; 
 int /*<<< orphan*/ * nvpair_allocv (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

nvpair_t *
nvpair_move_descriptor(const char *name, int value)
{
	nvpair_t *nvp;

	if (value < 0 || !fd_is_valid(value)) {
		ERRNO_SET(EBADF);
		return (NULL);
	}

	nvp = nvpair_allocv(name, NV_TYPE_DESCRIPTOR, (uint64_t)value,
	    sizeof(int64_t), 0);
	if (nvp == NULL) {
		ERRNO_SAVE();
		close(value);
		ERRNO_RESTORE();
	}

	return (nvp);
}