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
struct TYPE_2__ {scalar_t__ mle_type; } ;
struct mac_lomac {int ml_flags; TYPE_1__ ml_single; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAC_LOMAC_FLAG_SINGLE ; 
 scalar_t__ MAC_LOMAC_TYPE_HIGH ; 

__attribute__((used)) static int
lomac_high_single(struct mac_lomac *ml)
{

	KASSERT((ml->ml_flags & MAC_LOMAC_FLAG_SINGLE) != 0,
	    ("lomac_high_single: mac_lomac not single"));

	return (ml->ml_single.mle_type == MAC_LOMAC_TYPE_HIGH);
}