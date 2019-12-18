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

__attribute__((used)) static int oid_is_rsadsi(struct asn1_oid *oid)
{
	return oid->len >= 4 &&
		oid->oid[0] == 1 /* iso */ &&
		oid->oid[1] == 2 /* member-body */ &&
		oid->oid[2] == 840 /* us */ &&
		oid->oid[3] == 113549 /* rsadsi */;
}