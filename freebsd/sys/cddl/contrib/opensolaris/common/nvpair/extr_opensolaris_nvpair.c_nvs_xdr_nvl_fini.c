#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nvs_op; int /*<<< orphan*/ * nvs_private; } ;
typedef  TYPE_1__ nvstream_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ NVS_OP_ENCODE ; 
 int /*<<< orphan*/  xdr_int (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
nvs_xdr_nvl_fini(nvstream_t *nvs)
{
	if (nvs->nvs_op == NVS_OP_ENCODE) {
		XDR *xdr = nvs->nvs_private;
		int zero = 0;

		if (!xdr_int(xdr, &zero) || !xdr_int(xdr, &zero))
			return (EFAULT);
	}

	return (0);
}