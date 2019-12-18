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
struct xformsw {int dummy; } ;
struct secasvar {int /*<<< orphan*/  tdb_cryptoid; } ;
struct cryptoini {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V_crypto_support ; 
 int ah_init0 (struct secasvar*,struct xformsw*,struct cryptoini*) ; 
 int crypto_newsession (int /*<<< orphan*/ *,struct cryptoini*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ah_init(struct secasvar *sav, struct xformsw *xsp)
{
	struct cryptoini cria;
	int error;

	error = ah_init0(sav, xsp, &cria);
	return error ? error :
		 crypto_newsession(&sav->tdb_cryptoid, &cria, V_crypto_support);
}