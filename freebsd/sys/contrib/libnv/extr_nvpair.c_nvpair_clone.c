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

/* Variables and functions */
 int /*<<< orphan*/  NVPAIR_ASSERT (int /*<<< orphan*/  const*) ; 
#define  NV_TYPE_BINARY 139 
#define  NV_TYPE_BOOL 138 
#define  NV_TYPE_BOOL_ARRAY 137 
#define  NV_TYPE_DESCRIPTOR 136 
#define  NV_TYPE_DESCRIPTOR_ARRAY 135 
#define  NV_TYPE_NULL 134 
#define  NV_TYPE_NUMBER 133 
#define  NV_TYPE_NUMBER_ARRAY 132 
#define  NV_TYPE_NVLIST 131 
#define  NV_TYPE_NVLIST_ARRAY 130 
#define  NV_TYPE_STRING 129 
#define  NV_TYPE_STRING_ARRAY 128 
 int /*<<< orphan*/  PJDLOG_ABORT (char*,int) ; 
 int /*<<< orphan*/ * nvpair_create_binary (char const*,void const*,size_t) ; 
 int /*<<< orphan*/ * nvpair_create_bool (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvpair_create_bool_array (char const*,void const*,size_t) ; 
 int /*<<< orphan*/ * nvpair_create_descriptor (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvpair_create_descriptor_array (char const*,void const*,size_t) ; 
 int /*<<< orphan*/ * nvpair_create_null (char const*) ; 
 int /*<<< orphan*/ * nvpair_create_number (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvpair_create_number_array (char const*,void const*,size_t) ; 
 int /*<<< orphan*/ * nvpair_create_nvlist (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvpair_create_nvlist_array (char const*,void const*,size_t) ; 
 int /*<<< orphan*/ * nvpair_create_string (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvpair_create_string_array (char const*,void const*,size_t) ; 
 void* nvpair_get_binary (int /*<<< orphan*/  const*,size_t*) ; 
 int /*<<< orphan*/  nvpair_get_bool (int /*<<< orphan*/  const*) ; 
 void* nvpair_get_bool_array (int /*<<< orphan*/  const*,size_t*) ; 
 int /*<<< orphan*/  nvpair_get_descriptor (int /*<<< orphan*/  const*) ; 
 void* nvpair_get_descriptor_array (int /*<<< orphan*/  const*,size_t*) ; 
 int /*<<< orphan*/  nvpair_get_number (int /*<<< orphan*/  const*) ; 
 void* nvpair_get_number_array (int /*<<< orphan*/  const*,size_t*) ; 
 int /*<<< orphan*/  nvpair_get_nvlist (int /*<<< orphan*/  const*) ; 
 void* nvpair_get_nvlist_array (int /*<<< orphan*/  const*,size_t*) ; 
 int /*<<< orphan*/  nvpair_get_string (int /*<<< orphan*/  const*) ; 
 void* nvpair_get_string_array (int /*<<< orphan*/  const*,size_t*) ; 
 char* nvpair_name (int /*<<< orphan*/  const*) ; 
 int nvpair_type (int /*<<< orphan*/  const*) ; 

nvpair_t *
nvpair_clone(const nvpair_t *nvp)
{
	nvpair_t *newnvp;
	const char *name;
	const void *data;
	size_t datasize;

	NVPAIR_ASSERT(nvp);

	name = nvpair_name(nvp);

	switch (nvpair_type(nvp)) {
	case NV_TYPE_NULL:
		newnvp = nvpair_create_null(name);
		break;
	case NV_TYPE_BOOL:
		newnvp = nvpair_create_bool(name, nvpair_get_bool(nvp));
		break;
	case NV_TYPE_NUMBER:
		newnvp = nvpair_create_number(name, nvpair_get_number(nvp));
		break;
	case NV_TYPE_STRING:
		newnvp = nvpair_create_string(name, nvpair_get_string(nvp));
		break;
	case NV_TYPE_NVLIST:
		newnvp = nvpair_create_nvlist(name, nvpair_get_nvlist(nvp));
		break;
	case NV_TYPE_BINARY:
		data = nvpair_get_binary(nvp, &datasize);
		newnvp = nvpair_create_binary(name, data, datasize);
		break;
	case NV_TYPE_BOOL_ARRAY:
		data = nvpair_get_bool_array(nvp, &datasize);
		newnvp = nvpair_create_bool_array(name, data, datasize);
		break;
	case NV_TYPE_NUMBER_ARRAY:
		data = nvpair_get_number_array(nvp, &datasize);
		newnvp = nvpair_create_number_array(name, data, datasize);
		break;
	case NV_TYPE_STRING_ARRAY:
		data = nvpair_get_string_array(nvp, &datasize);
		newnvp = nvpair_create_string_array(name, data, datasize);
		break;
	case NV_TYPE_NVLIST_ARRAY:
		data = nvpair_get_nvlist_array(nvp, &datasize);
		newnvp = nvpair_create_nvlist_array(name, data, datasize);
		break;
#ifndef _KERNEL
	case NV_TYPE_DESCRIPTOR:
		newnvp = nvpair_create_descriptor(name,
		    nvpair_get_descriptor(nvp));
		break;
	case NV_TYPE_DESCRIPTOR_ARRAY:
		data = nvpair_get_descriptor_array(nvp, &datasize);
		newnvp = nvpair_create_descriptor_array(name, data, datasize);
		break;
#endif
	default:
		PJDLOG_ABORT("Unknown type: %d.", nvpair_type(nvp));
	}

	return (newnvp);
}