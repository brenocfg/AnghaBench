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
typedef  int /*<<< orphan*/  u_long ;
struct filecaps {int fc_nioctls; int /*<<< orphan*/ * fc_ioctls; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
filecaps_copy_finish(const struct filecaps *src, struct filecaps *dst,
    u_long *ioctls)
{
	size_t size;

	*dst = *src;
	if (__predict_true(src->fc_ioctls == NULL)) {
		MPASS(ioctls == NULL);
		return;
	}

	size = sizeof(src->fc_ioctls[0]) * src->fc_nioctls;
	dst->fc_ioctls = ioctls;
	bcopy(src->fc_ioctls, dst->fc_ioctls, size);
}