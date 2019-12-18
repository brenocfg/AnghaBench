#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ mle_type; } ;
struct TYPE_6__ {scalar_t__ mle_type; } ;
struct TYPE_4__ {scalar_t__ mle_type; } ;
struct mac_lomac {int ml_flags; TYPE_2__ ml_rangehigh; TYPE_3__ ml_rangelow; TYPE_1__ ml_single; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAC_LOMAC_FLAGS_BOTH ; 
 scalar_t__ MAC_LOMAC_TYPE_EQUAL ; 
 scalar_t__ MAC_LOMAC_TYPE_HIGH ; 
 scalar_t__ MAC_LOMAC_TYPE_LOW ; 

__attribute__((used)) static int
lomac_subject_privileged(struct mac_lomac *ml)
{

	KASSERT((ml->ml_flags & MAC_LOMAC_FLAGS_BOTH) ==
	    MAC_LOMAC_FLAGS_BOTH,
	    ("lomac_subject_privileged: subject doesn't have both labels"));

	/* If the single is EQUAL, it's ok. */
	if (ml->ml_single.mle_type == MAC_LOMAC_TYPE_EQUAL)
		return (0);

	/* If either range endpoint is EQUAL, it's ok. */
	if (ml->ml_rangelow.mle_type == MAC_LOMAC_TYPE_EQUAL ||
	    ml->ml_rangehigh.mle_type == MAC_LOMAC_TYPE_EQUAL)
		return (0);

	/* If the range is low-high, it's ok. */
	if (ml->ml_rangelow.mle_type == MAC_LOMAC_TYPE_LOW &&
	    ml->ml_rangehigh.mle_type == MAC_LOMAC_TYPE_HIGH)
		return (0);

	/* It's not ok. */
	return (EPERM);
}