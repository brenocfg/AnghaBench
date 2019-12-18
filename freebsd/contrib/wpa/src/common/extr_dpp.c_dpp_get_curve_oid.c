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
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 scalar_t__ OBJ_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OBJ_txt2obj (scalar_t__,int /*<<< orphan*/ ) ; 
 struct dpp_curve_params const* dpp_curves ; 

__attribute__((used)) static const struct dpp_curve_params *
dpp_get_curve_oid(const ASN1_OBJECT *poid)
{
	ASN1_OBJECT *oid;
	int i;

	for (i = 0; dpp_curves[i].name; i++) {
		oid = OBJ_txt2obj(dpp_curves[i].name, 0);
		if (oid && OBJ_cmp(poid, oid) == 0)
			return &dpp_curves[i];
	}
	return NULL;
}