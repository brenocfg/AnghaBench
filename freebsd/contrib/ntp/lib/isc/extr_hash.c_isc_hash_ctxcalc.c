#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int limit; } ;
typedef  TYPE_1__ isc_hash_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ VALID_HASH (TYPE_1__*) ; 
 unsigned int hash_calc (TYPE_1__*,unsigned char const*,unsigned int,int /*<<< orphan*/ ) ; 

unsigned int
isc_hash_ctxcalc(isc_hash_t *hctx, const unsigned char *key,
		 unsigned int keylen, isc_boolean_t case_sensitive)
{
	REQUIRE(hctx != NULL && VALID_HASH(hctx));
	REQUIRE(keylen <= hctx->limit);

	return (hash_calc(hctx, key, keylen, case_sensitive));
}