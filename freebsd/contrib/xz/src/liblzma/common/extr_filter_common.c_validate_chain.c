#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_4__ {scalar_t__ id; } ;
typedef  TYPE_1__ lzma_filter ;
struct TYPE_5__ {scalar_t__ id; int non_last_ok; int last_ok; scalar_t__ changes_size; } ;

/* Variables and functions */
 size_t LZMA_FILTERS_MAX ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 scalar_t__ LZMA_VLI_UNKNOWN ; 
 TYPE_3__* features ; 

__attribute__((used)) static lzma_ret
validate_chain(const lzma_filter *filters, size_t *count)
{
	// There must be at least one filter.
	if (filters == NULL || filters[0].id == LZMA_VLI_UNKNOWN)
		return LZMA_PROG_ERROR;

	// Number of non-last filters that may change the size of the data
	// significantly (that is, more than 1-2 % or so).
	size_t changes_size_count = 0;

	// True if it is OK to add a new filter after the current filter.
	bool non_last_ok = true;

	// True if the last filter in the given chain is actually usable as
	// the last filter. Only filters that support embedding End of Payload
	// Marker can be used as the last filter in the chain.
	bool last_ok = false;

	size_t i = 0;
	do {
		size_t j;
		for (j = 0; filters[i].id != features[j].id; ++j)
			if (features[j].id == LZMA_VLI_UNKNOWN)
				return LZMA_OPTIONS_ERROR;

		// If the previous filter in the chain cannot be a non-last
		// filter, the chain is invalid.
		if (!non_last_ok)
			return LZMA_OPTIONS_ERROR;

		non_last_ok = features[j].non_last_ok;
		last_ok = features[j].last_ok;
		changes_size_count += features[j].changes_size;

	} while (filters[++i].id != LZMA_VLI_UNKNOWN);

	// There must be 1-4 filters. The last filter must be usable as
	// the last filter in the chain. A maximum of three filters are
	// allowed to change the size of the data.
	if (i > LZMA_FILTERS_MAX || !last_ok || changes_size_count > 3)
		return LZMA_OPTIONS_ERROR;

	*count = i;
	return LZMA_OK;
}