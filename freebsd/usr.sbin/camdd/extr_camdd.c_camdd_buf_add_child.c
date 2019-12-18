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
struct camdd_buf_data {int /*<<< orphan*/  fill_len; } ;
struct TYPE_2__ {struct camdd_buf_data data; } ;
struct camdd_buf {scalar_t__ buf_type; int /*<<< orphan*/  src_count; int /*<<< orphan*/  src_list; TYPE_1__ buf_type_spec; } ;

/* Variables and functions */
 scalar_t__ CAMDD_BUF_DATA ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct camdd_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ camdd_buf_get_len (struct camdd_buf*) ; 
 int /*<<< orphan*/  src_links ; 

void
camdd_buf_add_child(struct camdd_buf *buf, struct camdd_buf *child_buf)
{
	struct camdd_buf_data *data;

	assert(buf->buf_type == CAMDD_BUF_DATA);

	data = &buf->buf_type_spec.data;

	STAILQ_INSERT_TAIL(&buf->src_list, child_buf, src_links);
	buf->src_count++;

	data->fill_len += camdd_buf_get_len(child_buf);
}