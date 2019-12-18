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
struct TYPE_2__ {int /*<<< orphan*/  mbe_compartments; void* mbe_grade; void* mbe_type; } ;
struct mac_biba {int /*<<< orphan*/  mb_flags; TYPE_1__ mb_effective; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_BIBA_FLAG_EFFECTIVE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
biba_set_effective(struct mac_biba *mb, u_short type, u_short grade,
    u_char *compartments)
{

	mb->mb_effective.mbe_type = type;
	mb->mb_effective.mbe_grade = grade;
	if (compartments != NULL)
		memcpy(mb->mb_effective.mbe_compartments, compartments,
		    sizeof(mb->mb_effective.mbe_compartments));
	mb->mb_flags |= MAC_BIBA_FLAG_EFFECTIVE;
}