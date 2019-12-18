#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_boolean_t ;
struct TYPE_4__ {unsigned int limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ VALID_HASH (TYPE_1__*) ; 
 TYPE_1__* hash ; 
 unsigned int hash_calc (TYPE_1__*,unsigned char const*,unsigned int,int /*<<< orphan*/ ) ; 

unsigned int
isc_hash_calc(const unsigned char *key, unsigned int keylen,
	      isc_boolean_t case_sensitive)
{
	INSIST(hash != NULL && VALID_HASH(hash));
	REQUIRE(keylen <= hash->limit);

	return (hash_calc(hash, key, keylen, case_sensitive));
}