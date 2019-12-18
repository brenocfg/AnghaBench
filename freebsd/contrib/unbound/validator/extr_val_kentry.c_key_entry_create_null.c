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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ time_t ;
struct regional {int dummy; } ;
struct key_entry_key {int dummy; } ;
struct key_entry_data {int /*<<< orphan*/ * algo; int /*<<< orphan*/ * rrset_data; int /*<<< orphan*/  rrset_type; int /*<<< orphan*/ * reason; scalar_t__ isbad; scalar_t__ ttl; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  key_entry_setup (struct regional*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,struct key_entry_key**,struct key_entry_data**) ; 

struct key_entry_key* 
key_entry_create_null(struct regional* region,
	uint8_t* name, size_t namelen, uint16_t dclass, time_t ttl,
	time_t now)
{
	struct key_entry_key* k;
	struct key_entry_data* d;
	if(!key_entry_setup(region, name, namelen, dclass, &k, &d))
		return NULL;
	d->ttl = now + ttl;
	d->isbad = 0;
	d->reason = NULL;
	d->rrset_type = LDNS_RR_TYPE_DNSKEY;
	d->rrset_data = NULL;
	d->algo = NULL;
	return k;
}