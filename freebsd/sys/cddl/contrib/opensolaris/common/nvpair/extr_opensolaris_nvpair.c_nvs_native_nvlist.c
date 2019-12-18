#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nvs_op; TYPE_2__* nvs_private; } ;
typedef  TYPE_1__ nvstream_t ;
struct TYPE_8__ {int n_flag; } ;
typedef  TYPE_2__ nvs_native_t ;
struct TYPE_9__ {int /*<<< orphan*/  nvl_nvflag; int /*<<< orphan*/  nvl_version; } ;
typedef  TYPE_3__ nvlist_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
#define  NVS_OP_DECODE 130 
#define  NVS_OP_ENCODE 129 
#define  NVS_OP_GETSIZE 128 
 int /*<<< orphan*/  native_cp (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
nvs_native_nvlist(nvstream_t *nvs, nvlist_t *nvl, size_t *size)
{
	nvs_native_t *native = nvs->nvs_private;

	switch (nvs->nvs_op) {
	case NVS_OP_ENCODE:
	case NVS_OP_DECODE:
		if (native->n_flag)
			return (0);	/* packed embedded list */

		native->n_flag = 1;

		/* copy version and nvflag of the nvlist_t */
		if (native_cp(nvs, &nvl->nvl_version, sizeof (int32_t)) != 0 ||
		    native_cp(nvs, &nvl->nvl_nvflag, sizeof (int32_t)) != 0)
			return (EFAULT);

		return (0);

	case NVS_OP_GETSIZE:
		/*
		 * if calculate for packed embedded list
		 * 	4 for end of the embedded list
		 * else
		 * 	2 * sizeof (int32_t) for nvl_version and nvl_nvflag
		 * 	and 4 for end of the entire list
		 */
		if (native->n_flag) {
			*size += 4;
		} else {
			native->n_flag = 1;
			*size += 2 * sizeof (int32_t) + 4;
		}

		return (0);

	default:
		return (EINVAL);
	}
}