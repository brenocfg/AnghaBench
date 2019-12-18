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
struct mac_lomac {int ml_flags; int /*<<< orphan*/  ml_rangehigh; int /*<<< orphan*/  ml_rangelow; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAC_LOMAC_FLAG_RANGE ; 

__attribute__((used)) static void
lomac_copy_range(struct mac_lomac *labelfrom, struct mac_lomac *labelto)
{

	KASSERT((labelfrom->ml_flags & MAC_LOMAC_FLAG_RANGE) != 0,
	    ("lomac_copy_range: labelfrom not range"));

	labelto->ml_rangelow = labelfrom->ml_rangelow;
	labelto->ml_rangehigh = labelfrom->ml_rangehigh;
	labelto->ml_flags |= MAC_LOMAC_FLAG_RANGE;
}