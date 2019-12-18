#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_5__ {int nvs_op; } ;
typedef  TYPE_1__ nvstream_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/ ** EMBEDDED_NVL_ARRAY (int /*<<< orphan*/ *) ; 
 size_t INT32_MAX ; 
 size_t NVP_NELEM (int /*<<< orphan*/ *) ; 
#define  NVS_OP_DECODE 130 
#define  NVS_OP_ENCODE 129 
#define  NVS_OP_GETSIZE 128 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  nvpair_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvs_embedded (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvs_operation (TYPE_1__*,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int
nvs_embedded_nvl_array(nvstream_t *nvs, nvpair_t *nvp, size_t *size)
{
	size_t nelem = NVP_NELEM(nvp);
	nvlist_t **nvlp = EMBEDDED_NVL_ARRAY(nvp);
	int i;

	switch (nvs->nvs_op) {
	case NVS_OP_ENCODE:
		for (i = 0; i < nelem; i++)
			if (nvs_embedded(nvs, nvlp[i]) != 0)
				return (EFAULT);
		break;

	case NVS_OP_DECODE: {
		size_t len = nelem * sizeof (uint64_t);
		nvlist_t *embedded = (nvlist_t *)((uintptr_t)nvlp + len);

		bzero(nvlp, len);	/* don't trust packed data */
		for (i = 0; i < nelem; i++) {
			if (nvs_embedded(nvs, embedded) != 0) {
				nvpair_free(nvp);
				return (EFAULT);
			}

			nvlp[i] = embedded++;
		}
		break;
	}
	case NVS_OP_GETSIZE: {
		uint64_t nvsize = 0;

		for (i = 0; i < nelem; i++) {
			size_t nvp_sz = 0;

			if (nvs_operation(nvs, nvlp[i], &nvp_sz) != 0)
				return (EINVAL);

			if ((nvsize += nvp_sz) > INT32_MAX)
				return (EINVAL);
		}

		*size = nvsize;
		break;
	}
	default:
		return (EINVAL);
	}

	return (0);
}