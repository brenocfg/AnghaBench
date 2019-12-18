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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {scalar_t__ nvp_type; int nvp_datasize; int /*<<< orphan*/  nvp_data; } ;
typedef  TYPE_1__ nvpair_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERRNO_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ NV_TYPE_NUMBER ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  be64dec (unsigned char const*) ; 
 int /*<<< orphan*/  le64dec (unsigned char const*) ; 

const unsigned char *
nvpair_unpack_number(bool isbe, nvpair_t *nvp, const unsigned char *ptr,
     size_t *leftp)
{

	PJDLOG_ASSERT(nvp->nvp_type == NV_TYPE_NUMBER);

	if (nvp->nvp_datasize != sizeof(uint64_t)) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}
	if (*leftp < sizeof(uint64_t)) {
		ERRNO_SET(EINVAL);
		return (NULL);
	}

	if (isbe)
		nvp->nvp_data = be64dec(ptr);
	else
		nvp->nvp_data = le64dec(ptr);

	ptr += sizeof(uint64_t);
	*leftp -= sizeof(uint64_t);

	return (ptr);
}