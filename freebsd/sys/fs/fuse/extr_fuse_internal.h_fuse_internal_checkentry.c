#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
struct fuse_entry_out {scalar_t__ nodeid; TYPE_1__ attr; } ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FUSE_NULL_ID ; 
 scalar_t__ FUSE_ROOT_ID ; 
 int IFTOVT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
fuse_internal_checkentry(struct fuse_entry_out *feo, enum vtype vtyp)
{
	if (vtyp != IFTOVT(feo->attr.mode)) {
		return (EINVAL);
	}

	if (feo->nodeid == FUSE_NULL_ID) {
		return (EINVAL);
	}

	if (feo->nodeid == FUSE_ROOT_ID) {
		return (EINVAL);
	}

	return (0);
}