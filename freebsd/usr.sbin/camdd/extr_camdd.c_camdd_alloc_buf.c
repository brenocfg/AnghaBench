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
typedef  int /*<<< orphan*/  uint8_t ;
struct camdd_dev {int blocksize; } ;
struct camdd_buf_data {int alloc_len; int /*<<< orphan*/ * buf; } ;
struct TYPE_2__ {struct camdd_buf_data data; } ;
struct camdd_buf {int buf_type; int /*<<< orphan*/  src_list; TYPE_1__ buf_type_spec; struct camdd_dev* dev; } ;
typedef  int camdd_buf_type ;

/* Variables and functions */
#define  CAMDD_BUF_DATA 129 
#define  CAMDD_BUF_INDIRECT 128 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct camdd_buf* calloc (int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static struct camdd_buf *
camdd_alloc_buf(struct camdd_dev *dev, camdd_buf_type buf_type)
{
	struct camdd_buf *buf = NULL;
	uint8_t *data_ptr = NULL;

	/*
	 * We only need to allocate data space for data buffers.
	 */
	switch (buf_type) {
	case CAMDD_BUF_DATA:
		data_ptr = malloc(dev->blocksize);
		if (data_ptr == NULL) {
			warn("unable to allocate %u bytes", dev->blocksize);
			goto bailout_error;
		}
		break;
	default:
		break;
	}
	
	buf = calloc(1, sizeof(*buf));
	if (buf == NULL) {
		warn("unable to allocate %zu bytes", sizeof(*buf));
		goto bailout_error;
	}

	buf->buf_type = buf_type;
	buf->dev = dev;
	switch (buf_type) {
	case CAMDD_BUF_DATA: {
		struct camdd_buf_data *data;

		data = &buf->buf_type_spec.data;

		data->alloc_len = dev->blocksize;
		data->buf = data_ptr;
		break;
	}
	case CAMDD_BUF_INDIRECT:
		break;
	default:
		break;
	}
	STAILQ_INIT(&buf->src_list);

	return (buf);

bailout_error:
	free(data_ptr);

	return (NULL);
}