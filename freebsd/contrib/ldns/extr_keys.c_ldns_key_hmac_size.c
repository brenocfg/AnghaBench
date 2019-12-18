#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t size; } ;
struct TYPE_6__ {TYPE_1__ hmac; } ;
struct TYPE_7__ {TYPE_2__ _key; } ;
typedef  TYPE_3__ ldns_key ;

/* Variables and functions */

size_t
ldns_key_hmac_size(const ldns_key *k)
{
	if (k->_key.hmac.size) {
		return k->_key.hmac.size;
	} else {
		return 0;
	}
}