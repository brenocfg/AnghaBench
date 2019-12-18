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
struct TYPE_3__ {int /*<<< orphan*/  mbe_compartments; void* mbe_grade; void* mbe_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  mbe_compartments; void* mbe_grade; void* mbe_type; } ;
struct mac_biba {int /*<<< orphan*/  mb_flags; TYPE_1__ mb_rangehigh; TYPE_2__ mb_rangelow; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_BIBA_FLAG_RANGE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
biba_set_range(struct mac_biba *mb, u_short typelow, u_short gradelow,
    u_char *compartmentslow, u_short typehigh, u_short gradehigh,
    u_char *compartmentshigh)
{

	mb->mb_rangelow.mbe_type = typelow;
	mb->mb_rangelow.mbe_grade = gradelow;
	if (compartmentslow != NULL)
		memcpy(mb->mb_rangelow.mbe_compartments, compartmentslow,
		    sizeof(mb->mb_rangelow.mbe_compartments));
	mb->mb_rangehigh.mbe_type = typehigh;
	mb->mb_rangehigh.mbe_grade = gradehigh;
	if (compartmentshigh != NULL)
		memcpy(mb->mb_rangehigh.mbe_compartments, compartmentshigh,
		    sizeof(mb->mb_rangehigh.mbe_compartments));
	mb->mb_flags |= MAC_BIBA_FLAG_RANGE;
}