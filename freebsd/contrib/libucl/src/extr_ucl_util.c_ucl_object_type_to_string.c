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
typedef  int ucl_type_t ;

/* Variables and functions */
#define  UCL_ARRAY 136 
#define  UCL_BOOLEAN 135 
#define  UCL_FLOAT 134 
#define  UCL_INT 133 
#define  UCL_NULL 132 
#define  UCL_OBJECT 131 
#define  UCL_STRING 130 
#define  UCL_TIME 129 
#define  UCL_USERDATA 128 

const char *
ucl_object_type_to_string (ucl_type_t type)
{
	const char *res = "unknown";

	switch (type) {
	case UCL_OBJECT:
		res = "object";
		break;
	case UCL_ARRAY:
		res = "array";
		break;
	case UCL_INT:
		res = "integer";
		break;
	case UCL_FLOAT:
	case UCL_TIME:
		res = "number";
		break;
	case UCL_STRING:
		res = "string";
		break;
	case UCL_BOOLEAN:
		res = "boolean";
		break;
	case UCL_USERDATA:
		res = "userdata";
		break;
	case UCL_NULL:
		res = "null";
		break;
	}

	return res;
}