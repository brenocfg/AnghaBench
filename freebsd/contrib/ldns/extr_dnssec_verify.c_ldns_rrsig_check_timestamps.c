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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_EXPIRATION_BEFORE_INCEPTION ; 
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_SIG_EXPIRED ; 
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_SIG_NOT_INCEPTED ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 scalar_t__ ldns_rdf2native_time_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_expiration (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_inception (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static ldns_status
ldns_rrsig_check_timestamps(const ldns_rr* rrsig, time_t now)
{
	int32_t inception, expiration;
	
	/* check the signature time stamps */
	inception = (int32_t)ldns_rdf2native_time_t(
		ldns_rr_rrsig_inception(rrsig));
	expiration = (int32_t)ldns_rdf2native_time_t(
		ldns_rr_rrsig_expiration(rrsig));

	if (expiration - inception < 0) {
		/* bad sig, expiration before inception?? Tsssg */
		return LDNS_STATUS_CRYPTO_EXPIRATION_BEFORE_INCEPTION;
	}
	if (((int32_t) now) - inception < 0) {
		/* bad sig, inception date has not yet come to pass */
		return LDNS_STATUS_CRYPTO_SIG_NOT_INCEPTED;
	}
	if (expiration - ((int32_t) now) < 0) {
		/* bad sig, expiration date has passed */
		return LDNS_STATUS_CRYPTO_SIG_EXPIRED;
	}
	return LDNS_STATUS_OK;
}