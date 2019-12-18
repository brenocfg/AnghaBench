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
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  des_block ;
struct TYPE_4__ {int /*<<< orphan*/  deskey; } ;
struct TYPE_5__ {scalar_t__ status; TYPE_1__ cryptkeyres_u; } ;
typedef  TYPE_2__ cryptkeyres ;

/* Variables and functions */
 scalar_t__ KEY_GET_CONV ; 
 scalar_t__ KEY_SUCCESS ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  key_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ xdr_cryptkeyres ; 
 scalar_t__ xdr_keybuf ; 

int
key_get_conv(char *pkey, des_block *deskey)
{
	cryptkeyres res;

	if (!key_call((u_long) KEY_GET_CONV, (xdrproc_t)xdr_keybuf, pkey,
			(xdrproc_t)xdr_cryptkeyres, &res)) {
		return (-1);
	}
	if (res.status != KEY_SUCCESS) {
		debug("get_conv status is nonzero");
		return (-1);
	}
	*deskey = res.cryptkeyres_u.deskey;
	return (0);
}