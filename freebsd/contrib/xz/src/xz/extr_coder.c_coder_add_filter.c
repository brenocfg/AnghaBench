#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_vli ;
struct TYPE_2__ {void* options; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 size_t LZMA_FILTERS_MAX ; 
 int /*<<< orphan*/  LZMA_PRESET_DEFAULT ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* filters ; 
 size_t filters_count ; 
 int /*<<< orphan*/  message_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preset_number ; 

extern void
coder_add_filter(lzma_vli id, void *options)
{
	if (filters_count == LZMA_FILTERS_MAX)
		message_fatal(_("Maximum number of filters is four"));

	filters[filters_count].id = id;
	filters[filters_count].options = options;
	++filters_count;

	// Setting a custom filter chain makes us forget the preset options.
	// This makes a difference if one specifies e.g. "xz -9 --lzma2 -e"
	// where the custom filter chain resets the preset level back to
	// the default 6, making the example equivalent to "xz -6e".
	preset_number = LZMA_PRESET_DEFAULT;

	return;
}