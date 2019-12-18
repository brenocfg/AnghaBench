#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nvs_op; scalar_t__ nvs_private; } ;
typedef  TYPE_1__ nvstream_t ;
struct TYPE_5__ {scalar_t__ n_curr; scalar_t__ n_end; } ;
typedef  TYPE_2__ nvs_native_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
#define  NVS_OP_DECODE 129 
#define  NVS_OP_ENCODE 128 
 int /*<<< orphan*/  bcopy (void*,void*,size_t) ; 

__attribute__((used)) static int
native_cp(nvstream_t *nvs, void *buf, size_t size)
{
	nvs_native_t *native = (nvs_native_t *)nvs->nvs_private;

	if (native->n_curr + size > native->n_end)
		return (EFAULT);

	/*
	 * The bcopy() below eliminates alignment requirement
	 * on the buffer (stream) and is preferred over direct access.
	 */
	switch (nvs->nvs_op) {
	case NVS_OP_ENCODE:
		bcopy(buf, native->n_curr, size);
		break;
	case NVS_OP_DECODE:
		bcopy(native->n_curr, buf, size);
		break;
	default:
		return (EINVAL);
	}

	native->n_curr += size;
	return (0);
}