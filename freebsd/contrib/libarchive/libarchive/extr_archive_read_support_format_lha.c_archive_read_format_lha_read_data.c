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
struct lha {scalar_t__ entry_is_compressed; int /*<<< orphan*/  entry_offset; scalar_t__ end_of_entry; scalar_t__ entry_unconsumed; } ;
struct archive_read {TYPE_1__* format; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,scalar_t__) ; 
 int lha_end_of_entry (struct archive_read*) ; 
 int lha_read_data_lzh (struct archive_read*,void const**,size_t*,int /*<<< orphan*/ *) ; 
 int lha_read_data_none (struct archive_read*,void const**,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
archive_read_format_lha_read_data(struct archive_read *a,
    const void **buff, size_t *size, int64_t *offset)
{
	struct lha *lha = (struct lha *)(a->format->data);
	int r;

	if (lha->entry_unconsumed) {
		/* Consume as much as the decompressor actually used. */
		__archive_read_consume(a, lha->entry_unconsumed);
		lha->entry_unconsumed = 0;
	}
	if (lha->end_of_entry) {
		*offset = lha->entry_offset;
		*size = 0;
		*buff = NULL;
		return (lha_end_of_entry(a));
	}

	if (lha->entry_is_compressed)
		r =  lha_read_data_lzh(a, buff, size, offset);
	else
		/* No compression. */
		r =  lha_read_data_none(a, buff, size, offset);
	return (r);
}