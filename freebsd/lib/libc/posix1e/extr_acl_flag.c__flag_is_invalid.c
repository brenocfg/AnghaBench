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
typedef  int acl_flag_t ;

/* Variables and functions */
 int ACL_FLAGS_BITS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int
_flag_is_invalid(acl_flag_t flag)
{

	if ((flag & ACL_FLAGS_BITS) == flag)
		return (0);

	errno = EINVAL;

	return (1);
}