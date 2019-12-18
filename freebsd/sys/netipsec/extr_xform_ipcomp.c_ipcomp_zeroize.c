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
struct secasvar {int /*<<< orphan*/ * tdb_cryptoid; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_freesession (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipcomp_zeroize(struct secasvar *sav)
{

	crypto_freesession(sav->tdb_cryptoid);
	sav->tdb_cryptoid = NULL;
	return 0;
}