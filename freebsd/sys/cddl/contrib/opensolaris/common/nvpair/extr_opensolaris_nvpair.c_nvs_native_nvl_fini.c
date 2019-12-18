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
struct TYPE_4__ {scalar_t__ nvs_op; scalar_t__ nvs_private; } ;
typedef  TYPE_1__ nvstream_t ;
struct TYPE_5__ {scalar_t__ n_curr; scalar_t__ n_end; } ;
typedef  TYPE_2__ nvs_native_t ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ NVS_OP_ENCODE ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 

__attribute__((used)) static int
nvs_native_nvl_fini(nvstream_t *nvs)
{
	if (nvs->nvs_op == NVS_OP_ENCODE) {
		nvs_native_t *native = (nvs_native_t *)nvs->nvs_private;
		/*
		 * Add 4 zero bytes at end of nvlist. They are used
		 * for end detection by the decode routine.
		 */
		if (native->n_curr + sizeof (int) > native->n_end)
			return (EFAULT);

		bzero(native->n_curr, sizeof (int));
		native->n_curr += sizeof (int);
	}

	return (0);
}