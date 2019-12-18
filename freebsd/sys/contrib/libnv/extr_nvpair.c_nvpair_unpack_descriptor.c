#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ nvp_type; int nvp_datasize; scalar_t__ nvp_data; } ;
typedef  TYPE_1__ nvpair_t ;
typedef  size_t int64_t ;
typedef  int /*<<< orphan*/  idx ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERRNO_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ NV_TYPE_DESCRIPTOR ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 size_t be64dec (unsigned char const*) ; 
 size_t le64dec (unsigned char const*) ; 

const unsigned char *
nvpair_unpack_descriptor(bool isbe, nvpair_t *nvp, const unsigned char *ptr,
    size_t *leftp, const int *fds, size_t nfds)
{
	int64_t idx;

	PJDLOG_ASSERT(nvp->nvp_type == NV_TYPE_DESCRIPTOR);

	if (nvp->nvp_datasize != sizeof(idx)) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}
	if (*leftp < sizeof(idx)) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}

	if (isbe)
		idx = be64dec(ptr);
	else
		idx = le64dec(ptr);

	if (idx < 0) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}

	if ((size_t)idx >= nfds) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}

	nvp->nvp_data = (uint64_t)fds[idx];

	ptr += sizeof(idx);
	*leftp -= sizeof(idx);

	return (ptr);
}