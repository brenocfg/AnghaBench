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
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_FILECAPS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ __predict_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_long *
filecaps_copy_prep(const struct filecaps *src)
{
	u_long *ioctls;
	size_t size;

	if (__predict_true(src->fc_ioctls == NULL))
		return (NULL);

	KASSERT(src->fc_nioctls > 0,
	    ("fc_ioctls != NULL, but fc_nioctls=%hd", src->fc_nioctls));

	size = sizeof(src->fc_ioctls[0]) * src->fc_nioctls;
	ioctls = malloc(size, M_FILECAPS, M_WAITOK);
	return (ioctls);
}