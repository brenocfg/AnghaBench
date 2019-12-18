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
typedef  void* u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  mme_compartments; void* mme_level; void* mme_type; } ;
struct mac_mls {int /*<<< orphan*/  mm_flags; TYPE_1__ mm_effective; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_MLS_FLAG_EFFECTIVE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
mls_set_effective(struct mac_mls *mm, u_short type, u_short level,
    u_char *compartments)
{

	mm->mm_effective.mme_type = type;
	mm->mm_effective.mme_level = level;
	if (compartments != NULL)
		memcpy(mm->mm_effective.mme_compartments, compartments,
		    sizeof(mm->mm_effective.mme_compartments));
	mm->mm_flags |= MAC_MLS_FLAG_EFFECTIVE;
}