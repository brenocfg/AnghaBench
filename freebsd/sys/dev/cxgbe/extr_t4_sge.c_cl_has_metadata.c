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
struct sge_fl {int flags; } ;
struct cluster_layout {scalar_t__ region1; scalar_t__ region3; } ;

/* Variables and functions */
 scalar_t__ CL_METADATA_SIZE ; 
 int FL_BUF_PACKING ; 
 int /*<<< orphan*/  MPASS (int) ; 

__attribute__((used)) static inline int
cl_has_metadata(struct sge_fl *fl, struct cluster_layout *cll)
{
	int rc = fl->flags & FL_BUF_PACKING || cll->region1 > 0;

	if (rc)
		MPASS(cll->region3 >= CL_METADATA_SIZE);

	return (rc);
}