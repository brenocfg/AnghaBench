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
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_owner_id ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_VALUES ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_CACHES ; 
 scalar_t__ ACPI_MUL_32 (scalar_t__) ; 
 scalar_t__ ACPI_NUM_OWNERID_MASKS ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_ALREADY_EXISTS ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OWNER_ID_LIMIT ; 
 scalar_t__ acpi_gbl_last_owner_id_index ; 
 scalar_t__ acpi_gbl_next_owner_id_offset ; 
 scalar_t__* acpi_gbl_owner_id_mask ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_allocate_owner_id ; 

acpi_status acpi_ut_allocate_owner_id(acpi_owner_id *owner_id)
{
	u32 i;
	u32 j;
	u32 k;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ut_allocate_owner_id);

	/* Guard against multiple allocations of ID to the same location */

	if (*owner_id) {
		ACPI_ERROR((AE_INFO,
			    "Owner ID [0x%3.3X] already exists", *owner_id));
		return_ACPI_STATUS(AE_ALREADY_EXISTS);
	}

	/* Mutex for the global ID mask */

	status = acpi_ut_acquire_mutex(ACPI_MTX_CACHES);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/*
	 * Find a free owner ID, cycle through all possible IDs on repeated
	 * allocations. (ACPI_NUM_OWNERID_MASKS + 1) because first index
	 * may have to be scanned twice.
	 */
	for (i = 0, j = acpi_gbl_last_owner_id_index;
	     i < (ACPI_NUM_OWNERID_MASKS + 1); i++, j++) {
		if (j >= ACPI_NUM_OWNERID_MASKS) {
			j = 0;	/* Wraparound to start of mask array */
		}

		for (k = acpi_gbl_next_owner_id_offset; k < 32; k++) {
			if (acpi_gbl_owner_id_mask[j] == ACPI_UINT32_MAX) {

				/* There are no free IDs in this mask */

				break;
			}

			/*
			 * Note: the u32 cast ensures that 1 is stored as a unsigned
			 * integer. Omitting the cast may result in 1 being stored as an
			 * int. Some compilers or runtime error detection may flag this as
			 * an error.
			 */
			if (!(acpi_gbl_owner_id_mask[j] & ((u32)1 << k))) {
				/*
				 * Found a free ID. The actual ID is the bit index plus one,
				 * making zero an invalid Owner ID. Save this as the last ID
				 * allocated and update the global ID mask.
				 */
				acpi_gbl_owner_id_mask[j] |= ((u32)1 << k);

				acpi_gbl_last_owner_id_index = (u8)j;
				acpi_gbl_next_owner_id_offset = (u8)(k + 1);

				/*
				 * Construct encoded ID from the index and bit position
				 *
				 * Note: Last [j].k (bit 4095) is never used and is marked
				 * permanently allocated (prevents +1 overflow)
				 */
				*owner_id =
				    (acpi_owner_id)((k + 1) + ACPI_MUL_32(j));

				ACPI_DEBUG_PRINT((ACPI_DB_VALUES,
						  "Allocated OwnerId: 0x%3.3X\n",
						  (unsigned int)*owner_id));
				goto exit;
			}
		}

		acpi_gbl_next_owner_id_offset = 0;
	}

	/*
	 * All owner_ids have been allocated. This typically should
	 * not happen since the IDs are reused after deallocation. The IDs are
	 * allocated upon table load (one per table) and method execution, and
	 * they are released when a table is unloaded or a method completes
	 * execution.
	 *
	 * If this error happens, there may be very deep nesting of invoked
	 * control methods, or there may be a bug where the IDs are not released.
	 */
	status = AE_OWNER_ID_LIMIT;
	ACPI_ERROR((AE_INFO,
		    "Could not allocate new OwnerId (4095 max), AE_OWNER_ID_LIMIT"));

exit:
	(void)acpi_ut_release_mutex(ACPI_MTX_CACHES);
	return_ACPI_STATUS(status);
}