#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct skd_special_context {unsigned char* data_buf; } ;
struct skd_device {int dummy; } ;

/* Variables and functions */
 int WR_BUF_SIZE ; 

__attribute__((used)) static int skd_chk_read_buf(struct skd_device *skdev,
			    struct skd_special_context *skspcl)
{
	unsigned char *buf = skspcl->data_buf;
	int i;

	/* check for incrementing byte pattern */
	for (i = 0; i < WR_BUF_SIZE; i++)
		if (buf[i] != (i & 0xFF))
			return 1;

	return 0;
}