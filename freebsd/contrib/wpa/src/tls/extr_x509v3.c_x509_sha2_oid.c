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

__attribute__((used)) static int x509_sha2_oid(struct asn1_oid *oid)
{
	return oid->len == 9 &&
		oid->oid[0] == 2 /* joint-iso-itu-t */ &&
		oid->oid[1] == 16 /* country */ &&
		oid->oid[2] == 840 /* us */ &&
		oid->oid[3] == 1 /* organization */ &&
		oid->oid[4] == 101 /* gov */ &&
		oid->oid[5] == 3 /* csor */ &&
		oid->oid[6] == 4 /* nistAlgorithm */ &&
		oid->oid[7] == 2 /* hashAlgs */;
}