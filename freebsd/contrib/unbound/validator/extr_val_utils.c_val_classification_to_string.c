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
typedef  enum val_classification { ____Placeholder_val_classification } val_classification ;

/* Variables and functions */
#define  VAL_CLASS_ANY 136 
#define  VAL_CLASS_CNAME 135 
#define  VAL_CLASS_CNAMENOANSWER 134 
#define  VAL_CLASS_NAMEERROR 133 
#define  VAL_CLASS_NODATA 132 
#define  VAL_CLASS_POSITIVE 131 
#define  VAL_CLASS_REFERRAL 130 
#define  VAL_CLASS_UNKNOWN 129 
#define  VAL_CLASS_UNTYPED 128 

const char*
val_classification_to_string(enum val_classification subtype)
{
	switch(subtype) {
		case VAL_CLASS_UNTYPED: 	return "untyped";
		case VAL_CLASS_UNKNOWN: 	return "unknown";
		case VAL_CLASS_POSITIVE: 	return "positive";
		case VAL_CLASS_CNAME: 		return "cname";
		case VAL_CLASS_NODATA: 		return "nodata";
		case VAL_CLASS_NAMEERROR: 	return "nameerror";
		case VAL_CLASS_CNAMENOANSWER: 	return "cnamenoanswer";
		case VAL_CLASS_REFERRAL: 	return "referral";
		case VAL_CLASS_ANY: 		return "qtype_any";
		default:
			return "bad_val_classification";
	}
}