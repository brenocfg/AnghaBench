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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
#define  DATA_TYPE_NVLIST 129 
#define  DATA_TYPE_NVLIST_ARRAY 128 
 int /*<<< orphan*/ * EMBEDDED_NVL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** EMBEDDED_NVL_ARRAY (int /*<<< orphan*/ *) ; 
 int NVP_NELEM (int /*<<< orphan*/ *) ; 
 int NVP_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvpair_free(nvpair_t *nvp)
{
	switch (NVP_TYPE(nvp)) {
	case DATA_TYPE_NVLIST:
		nvlist_free(EMBEDDED_NVL(nvp));
		break;
	case DATA_TYPE_NVLIST_ARRAY: {
		nvlist_t **nvlp = EMBEDDED_NVL_ARRAY(nvp);
		int i;

		for (i = 0; i < NVP_NELEM(nvp); i++)
			nvlist_free(nvlp[i]);
		break;
	}
	default:
		break;
	}
}