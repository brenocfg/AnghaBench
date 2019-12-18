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
struct asn1_oid {int len; int* oid; } ;

/* Variables and functions */

__attribute__((used)) static int x509_id_pkix_oid(struct asn1_oid *oid)
{
	return oid->len >= 7 &&
		oid->oid[0] == 1 /* iso */ &&
		oid->oid[1] == 3 /* identified-organization */ &&
		oid->oid[2] == 6 /* dod */ &&
		oid->oid[3] == 1 /* internet */ &&
		oid->oid[4] == 5 /* security */ &&
		oid->oid[5] == 5 /* mechanisms */ &&
		oid->oid[6] == 7 /* id-pkix */;
}