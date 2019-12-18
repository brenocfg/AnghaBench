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
struct voistatspec {int (* hlpr ) (int,struct voistatspec*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  hlprinfo; } ;
typedef  enum vsd_dtype { ____Placeholder_vsd_dtype } vsd_dtype ;

/* Variables and functions */
 int stub1 (int,struct voistatspec*,int /*<<< orphan*/ ) ; 

int
stats_vss_hlpr_init(enum vsd_dtype voi_dtype, uint32_t nvss,
    struct voistatspec *vss)
{
	int i, ret;

	for (i = nvss - 1; i >= 0; i--) {
		if (vss[i].hlpr && (ret = vss[i].hlpr(voi_dtype, &vss[i],
		    vss[i].hlprinfo)) != 0)
			return (ret);
	}

	return (0);
}