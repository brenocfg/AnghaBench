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
struct TYPE_3__ {int nvs_op; scalar_t__ nvs_private; } ;
typedef  TYPE_1__ nvstream_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
#define  NVS_OP_DECODE 129 
#define  NVS_OP_ENCODE 128 
 int /*<<< orphan*/  xdr_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvs_xdr_destroy(nvstream_t *nvs)
{
	switch (nvs->nvs_op) {
	case NVS_OP_ENCODE:
	case NVS_OP_DECODE:
		xdr_destroy((XDR *)nvs->nvs_private);
		break;
	default:
		break;
	}
}