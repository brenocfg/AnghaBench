#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nvs_op; int /*<<< orphan*/  nvs_recursion; int /*<<< orphan*/  nvs_priv; } ;
typedef  TYPE_1__ nvstream_t ;
typedef  int /*<<< orphan*/  nvpriv_t ;
struct TYPE_10__ {int /*<<< orphan*/  nvl_nvflag; int /*<<< orphan*/  nvl_version; } ;
typedef  TYPE_2__ nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUP ; 
#define  NVS_OP_DECODE 129 
#define  NVS_OP_ENCODE 128 
 int /*<<< orphan*/  NV_VERSION ; 
 int /*<<< orphan*/ * nv_priv_alloc_embedded (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (TYPE_2__*) ; 
 int /*<<< orphan*/  nvlist_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_max_recursion ; 
 int nvs_operation (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvs_embedded(nvstream_t *nvs, nvlist_t *embedded)
{
	switch (nvs->nvs_op) {
	case NVS_OP_ENCODE: {
		int err;

		if (nvs->nvs_recursion >= nvpair_max_recursion)
			return (EINVAL);
		nvs->nvs_recursion++;
		err = nvs_operation(nvs, embedded, NULL);
		nvs->nvs_recursion--;
		return (err);
	}
	case NVS_OP_DECODE: {
		nvpriv_t *priv;
		int err;

		if (embedded->nvl_version != NV_VERSION)
			return (ENOTSUP);

		if ((priv = nv_priv_alloc_embedded(nvs->nvs_priv)) == NULL)
			return (ENOMEM);

		nvlist_init(embedded, embedded->nvl_nvflag, priv);

		if (nvs->nvs_recursion >= nvpair_max_recursion) {
			nvlist_free(embedded);
			return (EINVAL);
		}
		nvs->nvs_recursion++;
		if ((err = nvs_operation(nvs, embedded, NULL)) != 0)
			nvlist_free(embedded);
		nvs->nvs_recursion--;
		return (err);
	}
	default:
		break;
	}

	return (EINVAL);
}