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
typedef  int /*<<< orphan*/  isc_hmacmd5_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_MD5_DIGESTLENGTH ; 
 int /*<<< orphan*/  isc_hmacmd5_verify2 (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

isc_boolean_t
isc_hmacmd5_verify(isc_hmacmd5_t *ctx, unsigned char *digest) {
	return (isc_hmacmd5_verify2(ctx, digest, ISC_MD5_DIGESTLENGTH));
}