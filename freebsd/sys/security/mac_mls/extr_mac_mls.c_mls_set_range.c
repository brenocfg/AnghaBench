#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int /*<<< orphan*/  mme_compartments; void* mme_level; void* mme_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  mme_compartments; void* mme_level; void* mme_type; } ;
struct mac_mls {int /*<<< orphan*/  mm_flags; TYPE_1__ mm_rangehigh; TYPE_2__ mm_rangelow; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_MLS_FLAG_RANGE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
mls_set_range(struct mac_mls *mm, u_short typelow, u_short levellow,
    u_char *compartmentslow, u_short typehigh, u_short levelhigh,
    u_char *compartmentshigh)
{

	mm->mm_rangelow.mme_type = typelow;
	mm->mm_rangelow.mme_level = levellow;
	if (compartmentslow != NULL)
		memcpy(mm->mm_rangelow.mme_compartments, compartmentslow,
		    sizeof(mm->mm_rangelow.mme_compartments));
	mm->mm_rangehigh.mme_type = typehigh;
	mm->mm_rangehigh.mme_level = levelhigh;
	if (compartmentshigh != NULL)
		memcpy(mm->mm_rangehigh.mme_compartments, compartmentshigh,
		    sizeof(mm->mm_rangehigh.mme_compartments));
	mm->mm_flags |= MAC_MLS_FLAG_RANGE;
}