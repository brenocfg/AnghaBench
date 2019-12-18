#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ max_allocation_length; int /*<<< orphan*/  extendable; scalar_t__ allocation_length; int /*<<< orphan*/  segment_list; int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_1__ ocs_textbuf_t ;
typedef  int /*<<< orphan*/  ocs_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ OCS_TEXTBUF_MAX_ALLOC_LEN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  ocs_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ocs_textbuf_segment_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_textbuf_segment_t ; 

int32_t
ocs_textbuf_alloc(ocs_t *ocs, ocs_textbuf_t *textbuf, uint32_t length)
{
	ocs_memset(textbuf, 0, sizeof(*textbuf));

	textbuf->ocs = ocs;
	ocs_list_init(&textbuf->segment_list, ocs_textbuf_segment_t, link);

	if (length > OCS_TEXTBUF_MAX_ALLOC_LEN) {
		textbuf->allocation_length = OCS_TEXTBUF_MAX_ALLOC_LEN;
	} else {
		textbuf->allocation_length = length;
	}

	/* mark as extendable */
	textbuf->extendable = TRUE;

	/* save maximum allocation length */
	textbuf->max_allocation_length = length;

	/* Add first segment */
	return (ocs_textbuf_segment_alloc(textbuf) == NULL) ? -1 : 0;
}