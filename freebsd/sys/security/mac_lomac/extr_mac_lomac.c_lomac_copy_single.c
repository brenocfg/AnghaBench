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
struct mac_lomac {int ml_flags; int /*<<< orphan*/  ml_single; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAC_LOMAC_FLAG_SINGLE ; 

__attribute__((used)) static void
lomac_copy_single(struct mac_lomac *labelfrom, struct mac_lomac *labelto)
{

	KASSERT((labelfrom->ml_flags & MAC_LOMAC_FLAG_SINGLE) != 0,
	    ("lomac_copy_single: labelfrom not single"));

	labelto->ml_single = labelfrom->ml_single;
	labelto->ml_flags |= MAC_LOMAC_FLAG_SINGLE;
}