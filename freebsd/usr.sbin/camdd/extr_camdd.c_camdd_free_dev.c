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
struct camdd_dev_pass {int /*<<< orphan*/ * dev; } ;
struct camdd_dev_file {int fd; struct camdd_dev* tmp_buf; } ;
struct TYPE_2__ {struct camdd_dev_pass pass; struct camdd_dev_file file; } ;
struct camdd_dev {int dev_type; TYPE_1__ dev_spec; } ;

/* Variables and functions */
#define  CAMDD_DEV_FILE 129 
#define  CAMDD_DEV_PASS 128 
 int /*<<< orphan*/  cam_close_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct camdd_dev*) ; 

void
camdd_free_dev(struct camdd_dev *dev)
{
	if (dev == NULL)
		return;

	switch (dev->dev_type) {
	case CAMDD_DEV_FILE: {
		struct camdd_dev_file *file_dev = &dev->dev_spec.file;

		if (file_dev->fd != -1)
			close(file_dev->fd);
		free(file_dev->tmp_buf);
		break;
	}
	case CAMDD_DEV_PASS: {
		struct camdd_dev_pass *pass_dev = &dev->dev_spec.pass;

		if (pass_dev->dev != NULL)
			cam_close_device(pass_dev->dev);
		break;
	}
	default:
		break;
	}

	free(dev);
}