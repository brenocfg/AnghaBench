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
struct vfsconf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * udf_zone_ds ; 
 int /*<<< orphan*/ * udf_zone_node ; 
 int /*<<< orphan*/ * udf_zone_trans ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
udf_uninit(struct vfsconf *foo)
{

	if (udf_zone_trans != NULL) {
		uma_zdestroy(udf_zone_trans);
		udf_zone_trans = NULL;
	}

	if (udf_zone_node != NULL) {
		uma_zdestroy(udf_zone_node);
		udf_zone_node = NULL;
	}

	if (udf_zone_ds != NULL) {
		uma_zdestroy(udf_zone_ds);
		udf_zone_ds = NULL;
	}

	return (0);
}