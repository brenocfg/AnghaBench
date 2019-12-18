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
struct TYPE_4__ {scalar_t__ key; } ;
struct TYPE_5__ {TYPE_1__ _key; } ;
typedef  TYPE_2__ ldns_key ;
typedef  int /*<<< orphan*/  DSA ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_PKEY_get1_DSA (scalar_t__) ; 

DSA *
ldns_key_dsa_key(const ldns_key *k)
{
#ifdef USE_DSA
	if (k->_key.key) {
		return EVP_PKEY_get1_DSA(k->_key.key);
	} else {
		return NULL;
	}
#else
	(void)k;
	return NULL;
#endif
}