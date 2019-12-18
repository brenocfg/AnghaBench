#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int val_storage; int refs; int data_storage; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_1__ bhnd_nvram_val ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int BHND_NVRAM_VAL_COPY_DATA ; 
#define  BHND_NVRAM_VAL_DATA_EXT_ALLOC 135 
#define  BHND_NVRAM_VAL_DATA_EXT_STATIC 134 
#define  BHND_NVRAM_VAL_DATA_EXT_WEAK 133 
#define  BHND_NVRAM_VAL_DATA_INLINE 132 
#define  BHND_NVRAM_VAL_DATA_NONE 131 
 int BHND_NVRAM_VAL_DYNAMIC ; 
 int /*<<< orphan*/  BHND_NVRAM_VAL_NEED_COPY (TYPE_1__*) ; 
 int BHND_NVRAM_VAL_STATIC_DATA ; 
#define  BHND_NVRAM_VAL_STORAGE_AUTO 130 
#define  BHND_NVRAM_VAL_STORAGE_DYNAMIC 129 
#define  BHND_NVRAM_VAL_STORAGE_STATIC 128 
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int /*<<< orphan*/  BHND_NV_LOG (char*,int) ; 
 int /*<<< orphan*/  BHND_NV_PANIC (char*,int) ; 
 void* bhnd_nvram_val_bytes (TYPE_1__*,size_t*,int /*<<< orphan*/ *) ; 
 int bhnd_nvram_val_new (TYPE_1__**,int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_acquire (int*) ; 

bhnd_nvram_val *
bhnd_nvram_val_copy(bhnd_nvram_val *value)
{
	bhnd_nvram_val		*result;
	const void		*bytes;
	bhnd_nvram_type		 type;
	size_t			 len;
	uint32_t		 flags;
	int			 error;

	switch (value->val_storage) {
	case BHND_NVRAM_VAL_STORAGE_STATIC:
		/* If static, can return as-is */
		return (value);

	case BHND_NVRAM_VAL_STORAGE_DYNAMIC:
		if (!BHND_NVRAM_VAL_NEED_COPY(value)) {
			refcount_acquire(&value->refs);
			return (value);
		}

		/* Perform copy below */
		break;

	case BHND_NVRAM_VAL_STORAGE_AUTO:
		BHND_NV_ASSERT(value->refs == 1, ("non-allocated value has "
		    "active refcount (%u)", value->refs));

		/* Perform copy below */
		break;
	}


	/* Compute the new value's flags based on the source value */
	switch (value->data_storage) {
	case BHND_NVRAM_VAL_DATA_NONE:
	case BHND_NVRAM_VAL_DATA_INLINE:
	case BHND_NVRAM_VAL_DATA_EXT_WEAK:
	case BHND_NVRAM_VAL_DATA_EXT_ALLOC:
		/* Copy the source data and permit additional allocation if the
		 * value cannot be represented inline */
		flags = BHND_NVRAM_VAL_COPY_DATA|BHND_NVRAM_VAL_DYNAMIC;
		break;
	case BHND_NVRAM_VAL_DATA_EXT_STATIC:
		flags = BHND_NVRAM_VAL_STATIC_DATA;
		break;
	default:
		BHND_NV_PANIC("invalid storage type: %d", value->data_storage);
	}

	/* Allocate new value copy */
	bytes = bhnd_nvram_val_bytes(value, &len, &type);
	error = bhnd_nvram_val_new(&result, value->fmt, bytes, len, type,
	    flags);
	if (error) {
		BHND_NV_LOG("copy failed: %d", error);
		return (NULL);
	}

	return (result);
}