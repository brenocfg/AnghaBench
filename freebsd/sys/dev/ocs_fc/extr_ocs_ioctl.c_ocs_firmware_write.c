#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ ocs_t ;
struct TYPE_13__ {scalar_t__ actual_xfer; scalar_t__ status; int /*<<< orphan*/  change_status; int /*<<< orphan*/  semaphore; } ;
typedef  TYPE_2__ ocs_mgmt_fw_write_result_t ;
struct TYPE_14__ {int /*<<< orphan*/  virt; } ;
typedef  TYPE_3__ ocs_dma_t ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int FW_WRITE_BUFSIZE ; 
 int /*<<< orphan*/  OCS_SEM_FOREVER ; 
 scalar_t__ ocs_dma_alloc (TYPE_1__*,TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  ocs_dma_free (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_fw_write_cb ; 
 int /*<<< orphan*/  ocs_hw_firmware_write (int /*<<< orphan*/ *,TYPE_3__*,int,int,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_log_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ocs_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ocs_sem_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ocs_firmware_write(ocs_t *ocs, const uint8_t *buf, size_t buf_len, 
						uint8_t *change_status)
{
        int rc = 0;
        uint32_t bytes_left;
        uint32_t xfer_size;
        uint32_t offset;
        ocs_dma_t dma;
        int last = 0;
        ocs_mgmt_fw_write_result_t result;

        ocs_sem_init(&(result.semaphore), 0, "fw_write");

        bytes_left = buf_len;
        offset = 0;

        if (ocs_dma_alloc(ocs, &dma, FW_WRITE_BUFSIZE, 4096)) {
                ocs_log_err(ocs, "ocs_firmware_write: malloc failed\n");
                return -ENOMEM;
        }

        while (bytes_left > 0) {

                if (bytes_left > FW_WRITE_BUFSIZE) {
                        xfer_size = FW_WRITE_BUFSIZE;
                } else {
                        xfer_size = bytes_left;
                }

                ocs_memcpy(dma.virt, buf + offset, xfer_size);

                if (bytes_left == xfer_size) {
                        last = 1;
                }

                ocs_hw_firmware_write(&ocs->hw, &dma, xfer_size, offset, 
						last, ocs_fw_write_cb, &result);

                if (ocs_sem_p(&(result.semaphore), OCS_SEM_FOREVER) != 0) {
                        rc = -ENXIO;
                        break;
                }

                if (result.actual_xfer == 0 || result.status != 0) {
                        rc = -EFAULT;
                        break;
                }

                if (last) {
                        *change_status = result.change_status;
                }

                bytes_left -= result.actual_xfer;
                offset += result.actual_xfer;
        }

        ocs_dma_free(ocs, &dma);
        return rc;
}