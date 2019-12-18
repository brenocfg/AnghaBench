#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nvp_type; } ;
typedef  TYPE_1__ nvpair_t ;
typedef  int /*<<< orphan*/  fd ;

/* Variables and functions */
 int /*<<< orphan*/  F_DUPFD_CLOEXEC ; 
 int /*<<< orphan*/  NVPAIR_ASSERT (TYPE_1__*) ; 
 scalar_t__ NV_TYPE_DESCRIPTOR_ARRAY ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int fcntl (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvpair_append (TYPE_1__*,int*,int,int) ; 

int
nvpair_append_descriptor_array(nvpair_t *nvp, const int value)
{
	int fd;

	NVPAIR_ASSERT(nvp);
	PJDLOG_ASSERT(nvp->nvp_type == NV_TYPE_DESCRIPTOR_ARRAY);
	fd = fcntl(value, F_DUPFD_CLOEXEC, 0);
	if (fd == -1) {
		return (-1);
	}
	if (nvpair_append(nvp, &fd, sizeof(fd), sizeof(fd)) == -1) {
		close(fd);
		return (-1);
	}
	return (0);
}