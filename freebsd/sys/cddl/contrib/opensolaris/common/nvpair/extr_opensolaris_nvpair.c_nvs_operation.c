#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int nvs_op; TYPE_1__* nvs_ops; } ;
typedef  TYPE_2__ nvstream_t ;
struct TYPE_16__ {scalar_t__ nvl_priv; } ;
typedef  TYPE_3__ nvlist_t ;
struct TYPE_14__ {int (* nvs_nvlist ) (TYPE_2__*,TYPE_3__*,size_t*) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
#define  NVS_OP_DECODE 130 
#define  NVS_OP_ENCODE 129 
#define  NVS_OP_GETSIZE 128 
 int nvs_decode_pairs (TYPE_2__*,TYPE_3__*) ; 
 int nvs_encode_pairs (TYPE_2__*,TYPE_3__*) ; 
 int nvs_getsize_pairs (TYPE_2__*,TYPE_3__*,size_t*) ; 
 int stub1 (TYPE_2__*,TYPE_3__*,size_t*) ; 

__attribute__((used)) static int
nvs_operation(nvstream_t *nvs, nvlist_t *nvl, size_t *buflen)
{
	int err;

	if (nvl->nvl_priv == 0)
		return (EFAULT);

	/*
	 * Perform the operation, starting with header, then each nvpair
	 */
	if ((err = nvs->nvs_ops->nvs_nvlist(nvs, nvl, buflen)) != 0)
		return (err);

	switch (nvs->nvs_op) {
	case NVS_OP_ENCODE:
		err = nvs_encode_pairs(nvs, nvl);
		break;

	case NVS_OP_DECODE:
		err = nvs_decode_pairs(nvs, nvl);
		break;

	case NVS_OP_GETSIZE:
		err = nvs_getsize_pairs(nvs, nvl, buflen);
		break;

	default:
		err = EINVAL;
	}

	return (err);
}