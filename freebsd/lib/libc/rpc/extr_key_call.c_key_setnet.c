#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  u_long ;
struct key_netstarg {int dummy; } ;
typedef  scalar_t__ keystatus ;

/* Variables and functions */
 scalar_t__ KEY_NET_PUT ; 
 scalar_t__ KEY_SUCCESS ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  key_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct key_netstarg*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ xdr_key_netstarg ; 
 scalar_t__ xdr_keystatus ; 

int
key_setnet(struct key_netstarg *arg)
{
	keystatus status;


	if (!key_call((u_long) KEY_NET_PUT, (xdrproc_t)xdr_key_netstarg, arg,
			(xdrproc_t)xdr_keystatus, &status)){
		return (-1);
	}

	if (status != KEY_SUCCESS) {
		debug("key_setnet status is nonzero");
		return (-1);
	}
	return (1);
}