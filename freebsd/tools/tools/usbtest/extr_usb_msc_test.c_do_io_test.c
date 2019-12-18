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
typedef  int uint8_t ;
typedef  unsigned int uint32_t ;
struct usb_msc_params {int io_mode; int io_offset; int io_delay; int io_size; scalar_t__ max_errors; int done; } ;
struct TYPE_2__ {scalar_t__ data_error; unsigned int xfer_rx_bytes; unsigned int xfer_tx_bytes; scalar_t__ xfer_error; scalar_t__ xfer_reset; } ;

/* Variables and functions */
#define  USB_MSC_IO_DELAY_FIXED_100MS 147 
#define  USB_MSC_IO_DELAY_FIXED_10MS 146 
#define  USB_MSC_IO_DELAY_RANDOM_100MS 145 
#define  USB_MSC_IO_DELAY_RANDOM_10MS 144 
#define  USB_MSC_IO_MODE_READ_WRITE 143 
#define  USB_MSC_IO_MODE_WRITE_ONLY 142 
#define  USB_MSC_IO_OFF_RANDOM 141 
#define  USB_MSC_IO_SIZE_FIXED_1024BLK 140 
#define  USB_MSC_IO_SIZE_FIXED_128BLK 139 
#define  USB_MSC_IO_SIZE_FIXED_16BLK 138 
#define  USB_MSC_IO_SIZE_FIXED_1BLK 137 
#define  USB_MSC_IO_SIZE_FIXED_256BLK 136 
#define  USB_MSC_IO_SIZE_FIXED_2BLK 135 
#define  USB_MSC_IO_SIZE_FIXED_32BLK 134 
#define  USB_MSC_IO_SIZE_FIXED_4BLK 133 
#define  USB_MSC_IO_SIZE_FIXED_512BLK 132 
#define  USB_MSC_IO_SIZE_FIXED_64BLK 131 
#define  USB_MSC_IO_SIZE_FIXED_8BLK 130 
#define  USB_MSC_IO_SIZE_INCREASING 129 
#define  USB_MSC_IO_SIZE_RANDOM 128 
 scalar_t__ bcmp (int*,int*,unsigned int) ; 
 unsigned int block_size ; 
 int do_read_10 (unsigned int,unsigned int,int*,int) ; 
 int do_write_10 (unsigned int,unsigned int,int*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__ stats ; 
 int usb_ts_rand_noise () ; 
 int /*<<< orphan*/  usleep (int) ; 
 unsigned int xfer_current_id ; 

__attribute__((used)) static void
do_io_test(struct usb_msc_params *p, uint8_t lun, uint32_t lba_max,
    uint8_t *buffer, uint8_t *reference)
{
	uint32_t io_offset;
	uint32_t io_size;
	uint32_t temp;
	uint8_t do_read;
	uint8_t retval;

	switch (p->io_mode) {
	case USB_MSC_IO_MODE_WRITE_ONLY:
		do_read = 0;
		break;
	case USB_MSC_IO_MODE_READ_WRITE:
		do_read = (usb_ts_rand_noise() & 1);
		break;
	default:
		do_read = 1;
		break;
	}

	switch (p->io_offset) {
	case USB_MSC_IO_OFF_RANDOM:
		io_offset = usb_ts_rand_noise();
		break;
	default:
		io_offset = 0;
		break;
	}

	switch (p->io_delay) {
	case USB_MSC_IO_DELAY_RANDOM_10MS:
		usleep(((uint32_t)usb_ts_rand_noise()) % 10000U);
		break;
	case USB_MSC_IO_DELAY_RANDOM_100MS:
		usleep(((uint32_t)usb_ts_rand_noise()) % 100000U);
		break;
	case USB_MSC_IO_DELAY_FIXED_10MS:
		usleep(10000);
		break;
	case USB_MSC_IO_DELAY_FIXED_100MS:
		usleep(100000);
		break;
	default:
		break;
	}

	switch (p->io_size) {
	case USB_MSC_IO_SIZE_RANDOM:
		io_size = ((uint32_t)usb_ts_rand_noise()) & 65535U;
		break;
	case USB_MSC_IO_SIZE_INCREASING:
		io_size = (xfer_current_id & 65535U);
		break;
	case USB_MSC_IO_SIZE_FIXED_1BLK:
		io_size = 1;
		break;
	case USB_MSC_IO_SIZE_FIXED_2BLK:
		io_size = 2;
		break;
	case USB_MSC_IO_SIZE_FIXED_4BLK:
		io_size = 4;
		break;
	case USB_MSC_IO_SIZE_FIXED_8BLK:
		io_size = 8;
		break;
	case USB_MSC_IO_SIZE_FIXED_16BLK:
		io_size = 16;
		break;
	case USB_MSC_IO_SIZE_FIXED_32BLK:
		io_size = 32;
		break;
	case USB_MSC_IO_SIZE_FIXED_64BLK:
		io_size = 64;
		break;
	case USB_MSC_IO_SIZE_FIXED_128BLK:
		io_size = 128;
		break;
	case USB_MSC_IO_SIZE_FIXED_256BLK:
		io_size = 256;
		break;
	case USB_MSC_IO_SIZE_FIXED_512BLK:
		io_size = 512;
		break;
	case USB_MSC_IO_SIZE_FIXED_1024BLK:
		io_size = 1024;
		break;
	default:
		io_size = 1;
		break;
	}

	if (io_size == 0)
		io_size = 1;

	io_offset %= lba_max;

	temp = (lba_max - io_offset);

	if (io_size > temp)
		io_size = temp;

	if (do_read) {
		retval = do_read_10(io_offset, io_size * block_size,
		    buffer + (io_offset * block_size), lun);

		if (retval == 0) {
			if (bcmp(buffer + (io_offset * block_size),
			    reference + (io_offset * block_size),
			    io_size * block_size)) {
				printf("ERROR: Data comparison failure\n");
				stats.data_error++;
				retval = 1;
			}
		}
		stats.xfer_rx_bytes += (io_size * block_size);

	} else {

		retval = do_write_10(io_offset, io_size * block_size,
		    reference + (io_offset * block_size), lun);

		stats.xfer_tx_bytes += (io_size * block_size);
	}

	if ((stats.xfer_error + stats.data_error +
	    stats.xfer_reset) >= p->max_errors) {
		printf("Maximum number of errors exceeded\n");
		p->done = 1;
	}
}