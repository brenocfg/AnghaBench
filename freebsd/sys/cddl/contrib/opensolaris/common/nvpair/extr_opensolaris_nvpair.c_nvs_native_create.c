#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nvs_op; TYPE_2__* nvs_private; } ;
typedef  TYPE_1__ nvstream_t ;
struct TYPE_6__ {char* n_curr; char* n_base; char* n_end; int /*<<< orphan*/  n_flag; } ;
typedef  TYPE_2__ nvs_native_t ;

/* Variables and functions */
 int EINVAL ; 
#define  NVS_OP_DECODE 130 
#define  NVS_OP_ENCODE 129 
#define  NVS_OP_GETSIZE 128 

__attribute__((used)) static int
nvs_native_create(nvstream_t *nvs, nvs_native_t *native, char *buf,
    size_t buflen)
{
	switch (nvs->nvs_op) {
	case NVS_OP_ENCODE:
	case NVS_OP_DECODE:
		nvs->nvs_private = native;
		native->n_curr = native->n_base = buf;
		native->n_end = buf + buflen;
		native->n_flag = 0;
		return (0);

	case NVS_OP_GETSIZE:
		nvs->nvs_private = native;
		native->n_curr = native->n_base = native->n_end = NULL;
		native->n_flag = 0;
		return (0);
	default:
		return (EINVAL);
	}
}