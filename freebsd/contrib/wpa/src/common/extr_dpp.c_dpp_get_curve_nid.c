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
struct dpp_curve_params {scalar_t__ name; } ;

/* Variables and functions */
 int OBJ_txt2nid (scalar_t__) ; 
 struct dpp_curve_params const* dpp_curves ; 

__attribute__((used)) static const struct dpp_curve_params * dpp_get_curve_nid(int nid)
{
	int i, tmp;

	if (!nid)
		return NULL;
	for (i = 0; dpp_curves[i].name; i++) {
		tmp = OBJ_txt2nid(dpp_curves[i].name);
		if (tmp == nid)
			return &dpp_curves[i];
	}
	return NULL;
}