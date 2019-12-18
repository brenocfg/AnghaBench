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
struct asn1_oid {int* oid; } ;

/* Variables and functions */
 scalar_t__ x509_sha2_oid (struct asn1_oid*) ; 

int x509_sha256_oid(struct asn1_oid *oid)
{
	return x509_sha2_oid(oid) &&
		oid->oid[8] == 1 /* sha256 */;
}