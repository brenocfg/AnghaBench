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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ time_t ;
struct val_env {scalar_t__ date_override; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct packed_rrset_data {scalar_t__ ttl; } ;
typedef  int /*<<< orphan*/  origttl ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  incep ;
typedef  int /*<<< orphan*/  expi ;

/* Variables and functions */
 scalar_t__ MIN_TTL ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  memmove (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ntohl (scalar_t__) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
adjust_ttl(struct val_env* ve, uint32_t unow, 
	struct ub_packed_rrset_key* rrset, uint8_t* orig_p, 
	uint8_t* expi_p, uint8_t* incep_p)
{
	struct packed_rrset_data* d = 
		(struct packed_rrset_data*)rrset->entry.data;
	/* read out the dates */
	int32_t origttl, expittl, expi, incep, now;
	memmove(&origttl, orig_p, sizeof(origttl));
	memmove(&expi, expi_p, sizeof(expi));
	memmove(&incep, incep_p, sizeof(incep));
	expi = ntohl(expi);
	incep = ntohl(incep);
	origttl = ntohl(origttl);

	/* get current date */
	if(ve->date_override) {
		now = ve->date_override;
	} else	now = (int32_t)unow;
	expittl = expi - now;

	/* so now:
	 * d->ttl: rrset ttl read from message or cache. May be reduced
	 * origttl: original TTL from signature, authoritative TTL max.
	 * MIN_TTL: minimum TTL from config.
	 * expittl: TTL until the signature expires.
	 *
	 * Use the smallest of these, but don't let origttl set the TTL
	 * below the minimum.
	 */
	if(MIN_TTL > (time_t)origttl && d->ttl > MIN_TTL) {
		verbose(VERB_QUERY, "rrset TTL larger than original and minimum"
			" TTL, adjusting TTL downwards to minimum ttl");
		d->ttl = MIN_TTL;
	}
	else if(MIN_TTL <= origttl && d->ttl > (time_t)origttl) {
		verbose(VERB_QUERY, "rrset TTL larger than original TTL, "
		"adjusting TTL downwards to original ttl");
		d->ttl = origttl;
	}

	if(expittl > 0 && d->ttl > (time_t)expittl) {
		verbose(VERB_ALGO, "rrset TTL larger than sig expiration ttl,"
			" adjusting TTL downwards");
		d->ttl = expittl;
	}
}