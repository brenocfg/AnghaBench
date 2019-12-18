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
typedef  int /*<<< orphan*/  des_block ;

/* Variables and functions */
 scalar_t__ KEY_GEN ; 
 int /*<<< orphan*/  key_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_des_block ; 
 scalar_t__ xdr_void ; 

int
key_gendes(des_block *key)
{
	if (!key_call((u_long)KEY_GEN, (xdrproc_t)xdr_void, NULL,
			(xdrproc_t)xdr_des_block, key)) {
		return (-1);
	}
	return (0);
}