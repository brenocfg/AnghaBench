#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s; } ;
struct private_b64encode {size_t bs; TYPE_1__ name; int /*<<< orphan*/  mode; int /*<<< orphan*/  encoded_buff; } ;
struct archive_write_filter {struct private_b64encode* data; TYPE_2__* archive; int /*<<< orphan*/  next_filter; } ;
struct TYPE_5__ {scalar_t__ magic; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  ENOMEM ; 
 int __archive_write_open_filter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * archive_string_ensure (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  archive_string_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t archive_write_get_bytes_per_block (TYPE_2__*) ; 

__attribute__((used)) static int
archive_filter_b64encode_open(struct archive_write_filter *f)
{
	struct private_b64encode *state = (struct private_b64encode *)f->data;
	size_t bs = 65536, bpb;
	int ret;

	ret = __archive_write_open_filter(f->next_filter);
	if (ret != ARCHIVE_OK)
		return (ret);

	if (f->archive->magic == ARCHIVE_WRITE_MAGIC) {
		/* Buffer size should be a multiple number of the of bytes
		 * per block for performance. */
		bpb = archive_write_get_bytes_per_block(f->archive);
		if (bpb > bs)
			bs = bpb;
		else if (bpb != 0)
			bs -= bs % bpb;
	}

	state->bs = bs;
	if (archive_string_ensure(&state->encoded_buff, bs + 512) == NULL) {
		archive_set_error(f->archive, ENOMEM,
		    "Can't allocate data for b64encode buffer");
		return (ARCHIVE_FATAL);
	}

	archive_string_sprintf(&state->encoded_buff, "begin-base64 %o %s\n",
	    state->mode, state->name.s);

	f->data = state;
	return (0);
}