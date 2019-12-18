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
struct TYPE_2__ {void* mle_grade; void* mle_type; } ;
struct mac_lomac {int /*<<< orphan*/  ml_flags; TYPE_1__ ml_single; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_LOMAC_FLAG_SINGLE ; 

__attribute__((used)) static void
lomac_set_single(struct mac_lomac *ml, u_short type, u_short grade)
{

	ml->ml_single.mle_type = type;
	ml->ml_single.mle_grade = grade;
	ml->ml_flags |= MAC_LOMAC_FLAG_SINGLE;
}