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
typedef  int uint_t ;
typedef  int data_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
#define  DATA_TYPE_BOOLEAN_ARRAY 129 
#define  DATA_TYPE_BOOLEAN_VALUE 128 
 int EINVAL ; 

__attribute__((used)) static int
i_validate_nvpair_value(data_type_t type, uint_t nelem, const void *data)
{
	switch (type) {
	case DATA_TYPE_BOOLEAN_VALUE:
		if (*(boolean_t *)data != B_TRUE &&
		    *(boolean_t *)data != B_FALSE)
			return (EINVAL);
		break;
	case DATA_TYPE_BOOLEAN_ARRAY: {
		int i;

		for (i = 0; i < nelem; i++)
			if (((boolean_t *)data)[i] != B_TRUE &&
			    ((boolean_t *)data)[i] != B_FALSE)
				return (EINVAL);
		break;
	}
	default:
		break;
	}

	return (0);
}