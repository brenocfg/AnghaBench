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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 long PNV_OCXL_TL_P9_RECV_CAP ; 
 int PNV_OCXL_TL_RATE_BUF_SIZE ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_templ_rate (int,int,char*) ; 

int pnv_ocxl_get_tl_cap(struct pci_dev *dev, long *cap,
			char *rate_buf, int rate_buf_size)
{
	if (rate_buf_size != PNV_OCXL_TL_RATE_BUF_SIZE)
		return -EINVAL;
	/*
	 * The TL capabilities are a characteristic of the NPU, so
	 * we go with hard-coded values.
	 *
	 * The receiving rate of each template is encoded on 4 bits.
	 *
	 * On P9:
	 * - templates 0 -> 3 are supported
	 * - templates 0, 1 and 3 have a 0 receiving rate
	 * - template 2 has receiving rate of 1 (extra cycle)
	 */
	memset(rate_buf, 0, rate_buf_size);
	set_templ_rate(2, 1, rate_buf);
	*cap = PNV_OCXL_TL_P9_RECV_CAP;
	return 0;
}