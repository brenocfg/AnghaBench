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
typedef  enum json_type { ____Placeholder_json_type } json_type ;

/* Variables and functions */
#define  JSON_ARRAY 134 
#define  JSON_BOOLEAN 133 
#define  JSON_NULL 132 
#define  JSON_NUMBER 131 
#define  JSON_OBJECT 130 
#define  JSON_STRING 129 
#define  JSON_VALUE 128 

__attribute__((used)) static const char * json_type_str(enum json_type type)
{
	switch (type) {
	case JSON_VALUE:
		return "VALUE";
	case JSON_OBJECT:
		return "OBJECT";
	case JSON_ARRAY:
		return "ARRAY";
	case JSON_STRING:
		return "STRING";
	case JSON_NUMBER:
		return "NUMBER";
	case JSON_BOOLEAN:
		return "BOOLEAN";
	case JSON_NULL:
		return "NULL";
	}
	return "??";
}