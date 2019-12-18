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

/* Variables and functions */
#define  TBMPString 144 
#define  TBitString 143 
#define  TBoolean 142 
#define  TEnumerated 141 
#define  TGeneralString 140 
#define  TGeneralizedTime 139 
#define  TIA5String 138 
#define  TInteger 137 
#define  TNull 136 
#define  TOID 135 
#define  TOctetString 134 
#define  TPrintableString 133 
#define  TTeletexString 132 
#define  TUTCTime 131 
#define  TUTF8String 130 
#define  TUniversalString 129 
#define  TVisibleString 128 

int
is_primitive_type(int type)
{
    switch(type) {
    case TInteger:
    case TBoolean:
    case TOctetString:
    case TBitString:
    case TEnumerated:
    case TGeneralizedTime:
    case TGeneralString:
    case TTeletexString:
    case TOID:
    case TUTCTime:
    case TUTF8String:
    case TPrintableString:
    case TIA5String:
    case TBMPString:
    case TUniversalString:
    case TVisibleString:
    case TNull:
	return 1;
    default:
	return 0;
    }
}