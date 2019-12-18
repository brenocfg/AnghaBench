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
typedef  int /*<<< orphan*/  uint32_t ;
struct camdd_buf_indirect {int /*<<< orphan*/  len; } ;
struct camdd_buf_data {int /*<<< orphan*/  fill_len; } ;
struct TYPE_2__ {struct camdd_buf_data data; struct camdd_buf_indirect indirect; } ;
struct camdd_buf {scalar_t__ buf_type; TYPE_1__ buf_type_spec; } ;

/* Variables and functions */
 scalar_t__ CAMDD_BUF_DATA ; 

uint32_t
camdd_buf_get_len(struct camdd_buf *buf)
{
	uint32_t len = 0;

	if (buf->buf_type != CAMDD_BUF_DATA) {
		struct camdd_buf_indirect *indirect;

		indirect = &buf->buf_type_spec.indirect;
		len = indirect->len;
	} else {
		struct camdd_buf_data *data;

		data = &buf->buf_type_spec.data;
		len = data->fill_len;
	}

	return (len);
}