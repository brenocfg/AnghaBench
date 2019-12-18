#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct secasvar {int /*<<< orphan*/ * tdb_xform; int /*<<< orphan*/ * tdb_authalgxform; int /*<<< orphan*/ * tdb_cryptoid; TYPE_1__* key_auth; } ;
struct TYPE_2__ {int /*<<< orphan*/  key_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  _KEYLEN (TYPE_1__*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_freesession (int /*<<< orphan*/ *) ; 

int
ah_zeroize(struct secasvar *sav)
{

	if (sav->key_auth)
		bzero(sav->key_auth->key_data, _KEYLEN(sav->key_auth));

	crypto_freesession(sav->tdb_cryptoid);
	sav->tdb_cryptoid = NULL;
	sav->tdb_authalgxform = NULL;
	sav->tdb_xform = NULL;
	return 0;
}