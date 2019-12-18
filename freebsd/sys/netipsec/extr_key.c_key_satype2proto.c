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
typedef  int uint8_t ;

/* Variables and functions */
 int IPPROTO_AH ; 
 int IPPROTO_ESP ; 
 int IPPROTO_IPCOMP ; 
 int IPPROTO_TCP ; 
 int IPSEC_PROTO_ANY ; 
#define  SADB_SATYPE_AH 132 
#define  SADB_SATYPE_ESP 131 
#define  SADB_SATYPE_UNSPEC 130 
#define  SADB_X_SATYPE_IPCOMP 129 
#define  SADB_X_SATYPE_TCPSIGNATURE 128 

__attribute__((used)) static uint8_t
key_satype2proto(uint8_t satype)
{
	switch (satype) {
	case SADB_SATYPE_UNSPEC:
		return IPSEC_PROTO_ANY;
	case SADB_SATYPE_AH:
		return IPPROTO_AH;
	case SADB_SATYPE_ESP:
		return IPPROTO_ESP;
	case SADB_X_SATYPE_IPCOMP:
		return IPPROTO_IPCOMP;
	case SADB_X_SATYPE_TCPSIGNATURE:
		return IPPROTO_TCP;
	default:
		return 0;
	}
	/* NOTREACHED */
}