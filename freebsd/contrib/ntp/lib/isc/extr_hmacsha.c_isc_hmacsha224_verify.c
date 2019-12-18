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
typedef  int /*<<< orphan*/  isc_hmacsha224_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int ISC_SHA224_DIGESTLENGTH ; 
 int /*<<< orphan*/  ISC_TF (int) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  isc_hmacsha224_sign (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ isc_tsmemcmp (unsigned char*,unsigned char*,size_t) ; 

isc_boolean_t
isc_hmacsha224_verify(isc_hmacsha224_t *ctx, unsigned char *digest, size_t len) {
	unsigned char newdigest[ISC_SHA224_DIGESTLENGTH];

	REQUIRE(len <= ISC_SHA224_DIGESTLENGTH);
	isc_hmacsha224_sign(ctx, newdigest, ISC_SHA224_DIGESTLENGTH);
	return (ISC_TF(isc_tsmemcmp(digest, newdigest, len) == 0));
}