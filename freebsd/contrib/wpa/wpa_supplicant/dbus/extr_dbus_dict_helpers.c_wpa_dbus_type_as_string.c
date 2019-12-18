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
#define  DBUS_TYPE_ARRAY 139 
 char const* DBUS_TYPE_ARRAY_AS_STRING ; 
#define  DBUS_TYPE_BOOLEAN 138 
 char const* DBUS_TYPE_BOOLEAN_AS_STRING ; 
#define  DBUS_TYPE_BYTE 137 
 char const* DBUS_TYPE_BYTE_AS_STRING ; 
#define  DBUS_TYPE_DOUBLE 136 
 char const* DBUS_TYPE_DOUBLE_AS_STRING ; 
#define  DBUS_TYPE_INT16 135 
 char const* DBUS_TYPE_INT16_AS_STRING ; 
#define  DBUS_TYPE_INT32 134 
 char const* DBUS_TYPE_INT32_AS_STRING ; 
#define  DBUS_TYPE_INT64 133 
 char const* DBUS_TYPE_INT64_AS_STRING ; 
#define  DBUS_TYPE_OBJECT_PATH 132 
 char const* DBUS_TYPE_OBJECT_PATH_AS_STRING ; 
#define  DBUS_TYPE_STRING 131 
 char const* DBUS_TYPE_STRING_AS_STRING ; 
#define  DBUS_TYPE_UINT16 130 
 char const* DBUS_TYPE_UINT16_AS_STRING ; 
#define  DBUS_TYPE_UINT32 129 
 char const* DBUS_TYPE_UINT32_AS_STRING ; 
#define  DBUS_TYPE_UINT64 128 
 char const* DBUS_TYPE_UINT64_AS_STRING ; 

const char * wpa_dbus_type_as_string(const int type)
{
	switch (type) {
	case DBUS_TYPE_BYTE:
		return DBUS_TYPE_BYTE_AS_STRING;
	case DBUS_TYPE_BOOLEAN:
		return DBUS_TYPE_BOOLEAN_AS_STRING;
	case DBUS_TYPE_INT16:
		return DBUS_TYPE_INT16_AS_STRING;
	case DBUS_TYPE_UINT16:
		return DBUS_TYPE_UINT16_AS_STRING;
	case DBUS_TYPE_INT32:
		return DBUS_TYPE_INT32_AS_STRING;
	case DBUS_TYPE_UINT32:
		return DBUS_TYPE_UINT32_AS_STRING;
	case DBUS_TYPE_INT64:
		return DBUS_TYPE_INT64_AS_STRING;
	case DBUS_TYPE_UINT64:
		return DBUS_TYPE_UINT64_AS_STRING;
	case DBUS_TYPE_DOUBLE:
		return DBUS_TYPE_DOUBLE_AS_STRING;
	case DBUS_TYPE_STRING:
		return DBUS_TYPE_STRING_AS_STRING;
	case DBUS_TYPE_OBJECT_PATH:
		return DBUS_TYPE_OBJECT_PATH_AS_STRING;
	case DBUS_TYPE_ARRAY:
		return DBUS_TYPE_ARRAY_AS_STRING;
	default:
		return NULL;
	}
}