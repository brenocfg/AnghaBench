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
#define  IPPROTO_AH 131 
#define  IPPROTO_ESP 130 
#define  IPPROTO_IPCOMP 129 
#define  IPPROTO_TCP 128 
 int SADB_SATYPE_AH ; 
 int SADB_SATYPE_ESP ; 
 int SADB_X_SATYPE_IPCOMP ; 
 int SADB_X_SATYPE_TCPSIGNATURE ; 

__attribute__((used)) static uint8_t
key_proto2satype(uint8_t proto)
{
	switch (proto) {
	case IPPROTO_AH:
		return SADB_SATYPE_AH;
	case IPPROTO_ESP:
		return SADB_SATYPE_ESP;
	case IPPROTO_IPCOMP:
		return SADB_X_SATYPE_IPCOMP;
	case IPPROTO_TCP:
		return SADB_X_SATYPE_TCPSIGNATURE;
	default:
		return 0;
	}
	/* NOTREACHED */
}