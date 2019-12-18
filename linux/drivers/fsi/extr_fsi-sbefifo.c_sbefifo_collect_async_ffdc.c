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
struct sbefifo {int async_ffdc; TYPE_1__* fsi_dev; } ;
struct kvec {void* iov_len; int /*<<< orphan*/ * iov_base; } ;
struct iov_iter {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int SBEFIFO_CMD_GET_SBE_FFDC ; 
 void* SBEFIFO_MAX_FFDC_SIZE ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_kvec (struct iov_iter*,int /*<<< orphan*/ ,struct kvec*,int,void*) ; 
 int sbefifo_do_command (struct sbefifo*,int /*<<< orphan*/ *,int,struct iov_iter*) ; 
 int /*<<< orphan*/  sbefifo_dump_ffdc (struct device*,int /*<<< orphan*/ *,size_t,int) ; 
 int sbefifo_parse_status (struct device*,int,int /*<<< orphan*/ *,size_t,size_t*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmalloc (void*) ; 

__attribute__((used)) static void sbefifo_collect_async_ffdc(struct sbefifo *sbefifo)
{
	struct device *dev = &sbefifo->fsi_dev->dev;
        struct iov_iter ffdc_iter;
        struct kvec ffdc_iov;
	__be32 *ffdc;
	size_t ffdc_sz;
	__be32 cmd[2];
	int rc;

	sbefifo->async_ffdc = false;
	ffdc = vmalloc(SBEFIFO_MAX_FFDC_SIZE);
	if (!ffdc) {
		dev_err(dev, "Failed to allocate SBE FFDC buffer\n");
		return;
	}
        ffdc_iov.iov_base = ffdc;
	ffdc_iov.iov_len = SBEFIFO_MAX_FFDC_SIZE;
        iov_iter_kvec(&ffdc_iter, WRITE, &ffdc_iov, 1, SBEFIFO_MAX_FFDC_SIZE);
	cmd[0] = cpu_to_be32(2);
	cmd[1] = cpu_to_be32(SBEFIFO_CMD_GET_SBE_FFDC);
	rc = sbefifo_do_command(sbefifo, cmd, 2, &ffdc_iter);
	if (rc != 0) {
		dev_err(dev, "Error %d retrieving SBE FFDC\n", rc);
		goto bail;
	}
	ffdc_sz = SBEFIFO_MAX_FFDC_SIZE - iov_iter_count(&ffdc_iter);
	ffdc_sz /= sizeof(__be32);
	rc = sbefifo_parse_status(dev, SBEFIFO_CMD_GET_SBE_FFDC, ffdc,
				  ffdc_sz, &ffdc_sz);
	if (rc != 0) {
		dev_err(dev, "Error %d decoding SBE FFDC\n", rc);
		goto bail;
	}
	if (ffdc_sz > 0)
		sbefifo_dump_ffdc(dev, ffdc, ffdc_sz, true);
 bail:
	vfree(ffdc);

}