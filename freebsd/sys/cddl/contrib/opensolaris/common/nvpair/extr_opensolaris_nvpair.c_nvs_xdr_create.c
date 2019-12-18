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
typedef  int ulong_t ;
typedef  int /*<<< orphan*/  uint_t ;
struct TYPE_3__ {int nvs_op; int /*<<< orphan*/ * nvs_private; } ;
typedef  TYPE_1__ nvstream_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
#define  NVS_OP_DECODE 130 
#define  NVS_OP_ENCODE 129 
#define  NVS_OP_GETSIZE 128 
 int /*<<< orphan*/  XDR_DECODE ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 int /*<<< orphan*/  xdrmem_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvs_xdr_create(nvstream_t *nvs, XDR *xdr, char *buf, size_t buflen)
{
	/* xdr data must be 4 byte aligned */
	if ((ulong_t)buf % 4 != 0)
		return (EFAULT);

	switch (nvs->nvs_op) {
	case NVS_OP_ENCODE:
		xdrmem_create(xdr, buf, (uint_t)buflen, XDR_ENCODE);
		nvs->nvs_private = xdr;
		return (0);
	case NVS_OP_DECODE:
		xdrmem_create(xdr, buf, (uint_t)buflen, XDR_DECODE);
		nvs->nvs_private = xdr;
		return (0);
	case NVS_OP_GETSIZE:
		nvs->nvs_private = NULL;
		return (0);
	default:
		return (EINVAL);
	}
}