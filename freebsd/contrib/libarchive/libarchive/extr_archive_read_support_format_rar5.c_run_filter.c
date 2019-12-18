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
struct TYPE_2__ {int /*<<< orphan*/  last_write_ptr; int /*<<< orphan*/  filtered_buf; } ;
struct rar5 {TYPE_1__ cstate; } ;
struct filter_info {int type; int /*<<< orphan*/  block_length; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_PROGRAMMER ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  FILTER_ARM 131 
#define  FILTER_DELTA 130 
#define  FILTER_E8 129 
#define  FILTER_E8E9 128 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 struct rar5* get_context (struct archive_read*) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int push_data_ready (struct archive_read*,struct rar5*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int run_arm_filter (struct rar5*,struct filter_info*) ; 
 int run_delta_filter (struct rar5*,struct filter_info*) ; 
 int run_e8e9_filter (struct rar5*,struct filter_info*,int) ; 

__attribute__((used)) static int run_filter(struct archive_read* a, struct filter_info* flt) {
	int ret;
	struct rar5* rar = get_context(a);

	free(rar->cstate.filtered_buf);

	rar->cstate.filtered_buf = malloc(flt->block_length);
	if(!rar->cstate.filtered_buf) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for filter data.");
		return ARCHIVE_FATAL;
	}

	switch(flt->type) {
		case FILTER_DELTA:
			ret = run_delta_filter(rar, flt);
			break;

		case FILTER_E8:
			/* fallthrough */
		case FILTER_E8E9:
			ret = run_e8e9_filter(rar, flt,
			    flt->type == FILTER_E8E9);
			break;

		case FILTER_ARM:
			ret = run_arm_filter(rar, flt);
			break;

		default:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Unsupported filter type: 0x%x", flt->type);
			return ARCHIVE_FATAL;
	}

	if(ret != ARCHIVE_OK) {
		/* Filter has failed. */
		return ret;
	}

	if(ARCHIVE_OK != push_data_ready(a, rar, rar->cstate.filtered_buf,
	    flt->block_length, rar->cstate.last_write_ptr))
	{
		archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
		    "Stack overflow when submitting unpacked data");

		return ARCHIVE_FATAL;
	}

	rar->cstate.last_write_ptr += flt->block_length;
	return ARCHIVE_OK;
}