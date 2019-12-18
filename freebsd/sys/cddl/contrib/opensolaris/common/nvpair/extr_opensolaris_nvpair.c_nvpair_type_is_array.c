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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  scalar_t__ data_type_t ;

/* Variables and functions */
 scalar_t__ DATA_TYPE_BOOLEAN_ARRAY ; 
 scalar_t__ DATA_TYPE_BYTE_ARRAY ; 
 scalar_t__ DATA_TYPE_INT16_ARRAY ; 
 scalar_t__ DATA_TYPE_INT32_ARRAY ; 
 scalar_t__ DATA_TYPE_INT64_ARRAY ; 
 scalar_t__ DATA_TYPE_INT8_ARRAY ; 
 scalar_t__ DATA_TYPE_NVLIST_ARRAY ; 
 scalar_t__ DATA_TYPE_STRING_ARRAY ; 
 scalar_t__ DATA_TYPE_UINT16_ARRAY ; 
 scalar_t__ DATA_TYPE_UINT32_ARRAY ; 
 scalar_t__ DATA_TYPE_UINT64_ARRAY ; 
 scalar_t__ DATA_TYPE_UINT8_ARRAY ; 
 scalar_t__ NVP_TYPE (int /*<<< orphan*/ *) ; 

int
nvpair_type_is_array(nvpair_t *nvp)
{
	data_type_t type = NVP_TYPE(nvp);

	if ((type == DATA_TYPE_BYTE_ARRAY) ||
	    (type == DATA_TYPE_INT8_ARRAY) ||
	    (type == DATA_TYPE_UINT8_ARRAY) ||
	    (type == DATA_TYPE_INT16_ARRAY) ||
	    (type == DATA_TYPE_UINT16_ARRAY) ||
	    (type == DATA_TYPE_INT32_ARRAY) ||
	    (type == DATA_TYPE_UINT32_ARRAY) ||
	    (type == DATA_TYPE_INT64_ARRAY) ||
	    (type == DATA_TYPE_UINT64_ARRAY) ||
	    (type == DATA_TYPE_BOOLEAN_ARRAY) ||
	    (type == DATA_TYPE_STRING_ARRAY) ||
	    (type == DATA_TYPE_NVLIST_ARRAY))
		return (1);
	return (0);

}