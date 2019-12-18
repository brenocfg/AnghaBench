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
struct ecc_curve {int dummy; } ;
typedef  enum OID { ____Placeholder_OID } OID ;

/* Variables and functions */
#define  OID_gostCPSignA 137 
#define  OID_gostCPSignB 136 
#define  OID_gostCPSignC 135 
#define  OID_gostTC26Sign256A 134 
#define  OID_gostTC26Sign256B 133 
#define  OID_gostTC26Sign256C 132 
#define  OID_gostTC26Sign256D 131 
#define  OID_gostTC26Sign512A 130 
#define  OID_gostTC26Sign512B 129 
#define  OID_gostTC26Sign512C 128 
 struct ecc_curve const gost_cp256a ; 
 struct ecc_curve const gost_cp256b ; 
 struct ecc_curve const gost_cp256c ; 
 struct ecc_curve const gost_tc512a ; 
 struct ecc_curve const gost_tc512b ; 

__attribute__((used)) static const struct ecc_curve *get_curve_by_oid(enum OID oid)
{
	switch (oid) {
	case OID_gostCPSignA:
	case OID_gostTC26Sign256B:
		return &gost_cp256a;
	case OID_gostCPSignB:
	case OID_gostTC26Sign256C:
		return &gost_cp256b;
	case OID_gostCPSignC:
	case OID_gostTC26Sign256D:
		return &gost_cp256c;
	case OID_gostTC26Sign512A:
		return &gost_tc512a;
	case OID_gostTC26Sign512B:
		return &gost_tc512b;
	/* The following two aren't implemented: */
	case OID_gostTC26Sign256A:
	case OID_gostTC26Sign512C:
	default:
		return NULL;
	}
}