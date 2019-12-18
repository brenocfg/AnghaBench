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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  NVP_NAME (int /*<<< orphan*/ *) ; 
 scalar_t__ NVP_TYPE (int /*<<< orphan*/ *) ; 
 int NV_UNIQUE_NAME ; 
 int NV_UNIQUE_NAME_TYPE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
nvt_nvpair_match(nvpair_t *nvp1, nvpair_t *nvp2, uint32_t nvflag)
{
	boolean_t match = B_FALSE;
	if (nvflag & NV_UNIQUE_NAME_TYPE) {
		if (strcmp(NVP_NAME(nvp1), NVP_NAME(nvp2)) == 0 &&
		    NVP_TYPE(nvp1) == NVP_TYPE(nvp2))
			match = B_TRUE;
	} else {
		ASSERT(nvflag == 0 || nvflag & NV_UNIQUE_NAME);
		if (strcmp(NVP_NAME(nvp1), NVP_NAME(nvp2)) == 0)
			match = B_TRUE;
	}
	return (match);
}