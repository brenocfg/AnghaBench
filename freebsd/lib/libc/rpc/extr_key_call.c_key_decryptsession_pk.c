#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  netobj ;
typedef  int /*<<< orphan*/  des_block ;
struct TYPE_6__ {int /*<<< orphan*/  deskey; } ;
struct TYPE_7__ {scalar_t__ status; TYPE_1__ cryptkeyres_u; } ;
typedef  TYPE_2__ cryptkeyres ;
struct TYPE_8__ {char* remotename; int /*<<< orphan*/  deskey; int /*<<< orphan*/  remotekey; } ;
typedef  TYPE_3__ cryptkeyarg2 ;

/* Variables and functions */
 scalar_t__ KEY_DECRYPT_PK ; 
 scalar_t__ KEY_SUCCESS ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  key_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ xdr_cryptkeyarg2 ; 
 scalar_t__ xdr_cryptkeyres ; 

int
key_decryptsession_pk(char *remotename, netobj *remotekey, des_block *deskey)
{
	cryptkeyarg2 arg;
	cryptkeyres res;

	arg.remotename = remotename;
	arg.remotekey = *remotekey;
	arg.deskey = *deskey;
	if (!key_call((u_long)KEY_DECRYPT_PK, (xdrproc_t)xdr_cryptkeyarg2, &arg,
			(xdrproc_t)xdr_cryptkeyres, &res)) {
		return (-1);
	}
	if (res.status != KEY_SUCCESS) {
		debug("decrypt status is nonzero");
		return (-1);
	}
	*deskey = res.cryptkeyres_u.deskey;
	return (0);
}