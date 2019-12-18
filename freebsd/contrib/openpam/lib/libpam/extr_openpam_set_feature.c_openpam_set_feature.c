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
struct TYPE_2__ {int onoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTERF (int) ; 
 int OPENPAM_NUM_FEATURES ; 
 int /*<<< orphan*/  PAM_BAD_FEATURE ; 
 int /*<<< orphan*/  PAM_SUCCESS ; 
 int /*<<< orphan*/  RETURNC (int /*<<< orphan*/ ) ; 
 TYPE_1__* openpam_features ; 

int
openpam_set_feature(int feature, int onoff)
{

	ENTERF(feature);
	if (feature < 0 || feature >= OPENPAM_NUM_FEATURES)
		RETURNC(PAM_BAD_FEATURE);
	openpam_features[feature].onoff = onoff;
	RETURNC(PAM_SUCCESS);
}