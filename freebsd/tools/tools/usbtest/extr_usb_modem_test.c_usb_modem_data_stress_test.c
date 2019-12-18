#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ time_t ;
struct timeval {scalar_t__ tv_sec; } ;
struct TYPE_4__ {scalar_t__ bytes; } ;
struct TYPE_3__ {scalar_t__ bytes; } ;
struct modem {scalar_t__ loop_data; int /*<<< orphan*/  xfer_out; int /*<<< orphan*/  xfer_in; int /*<<< orphan*/  usb_dev; scalar_t__ random_tx_delay; scalar_t__ random_tx_length; scalar_t__ errors; TYPE_2__ tx_bytes; TYPE_1__ rx_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 scalar_t__ libusb20_dev_check_connected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb20_dev_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb20_dev_wait_process (int /*<<< orphan*/ ,int) ; 
 scalar_t__ libusb20_tr_get_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ libusb20_tr_get_max_total_length (int /*<<< orphan*/ ) ; 
 scalar_t__ libusb20_tr_get_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb20_tr_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb20_tr_setup_bulk (int /*<<< orphan*/ ,int*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb20_tr_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb20_tr_stop (int /*<<< orphan*/ ) ; 
 int* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int*,scalar_t__) ; 
 int /*<<< orphan*/  modem_read (int*,scalar_t__) ; 
 int /*<<< orphan*/  modem_write (int*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 scalar_t__ usb_ts_rand_noise () ; 
 int /*<<< orphan*/  usleep (scalar_t__) ; 

__attribute__((used)) static void
usb_modem_data_stress_test(struct modem *p, uint32_t duration)
{
	struct timeval sub_tv;
	struct timeval ref_tv;
	struct timeval res_tv;

	time_t last_sec;

	uint8_t in_pending = 0;
	uint8_t in_ready = 0;
	uint8_t out_pending = 0;

	uint32_t id = 0;

	uint32_t in_max;
	uint32_t out_max;
	uint32_t io_max;

	uint8_t *in_buffer = 0;
	uint8_t *out_buffer = 0;

	gettimeofday(&ref_tv, 0);

	last_sec = ref_tv.tv_sec;

	printf("\n");

	in_max = libusb20_tr_get_max_total_length(p->xfer_in);
	out_max = libusb20_tr_get_max_total_length(p->xfer_out);

	/* get the smallest buffer size and use that */
	io_max = (in_max < out_max) ? in_max : out_max;

	if (in_max != out_max)
		printf("WARNING: Buffer sizes are un-equal: %u vs %u\n", in_max, out_max);

	in_buffer = malloc(io_max);
	if (in_buffer == NULL)
		goto fail;

	out_buffer = malloc(io_max);
	if (out_buffer == NULL)
		goto fail;

	while (1) {

		gettimeofday(&sub_tv, 0);

		if (last_sec != sub_tv.tv_sec) {

			printf("STATUS: ID=%u, RX=%u bytes/sec, TX=%u bytes/sec, ERR=%d\n",
			    (int)id,
			    (int)p->rx_bytes.bytes,
			    (int)p->tx_bytes.bytes,
			    (int)p->errors);

			p->rx_bytes.bytes = 0;
			p->tx_bytes.bytes = 0;

			fflush(stdout);

			last_sec = sub_tv.tv_sec;

			id++;
		}
		timersub(&sub_tv, &ref_tv, &res_tv);

		if ((res_tv.tv_sec < 0) || (res_tv.tv_sec >= (int)duration))
			break;

		libusb20_dev_process(p->usb_dev);

		if (!libusb20_tr_pending(p->xfer_in)) {
			if (in_pending) {
				if (libusb20_tr_get_status(p->xfer_in) == 0) {
					modem_read(in_buffer, libusb20_tr_get_length(p->xfer_in, 0));
				} else {
					p->errors++;
					usleep(10000);
				}
				in_pending = 0;
				in_ready = 1;
			}
			if (p->loop_data == 0) {
				libusb20_tr_setup_bulk(p->xfer_in, in_buffer, io_max, 0);
				libusb20_tr_start(p->xfer_in);
				in_pending = 1;
				in_ready = 0;
			}
		}
		if (!libusb20_tr_pending(p->xfer_out)) {

			uint32_t len;
			uint32_t dly;

			if (out_pending) {
				if (libusb20_tr_get_status(p->xfer_out) != 0) {
					p->errors++;
					usleep(10000);
				}
			}
			if (p->random_tx_length) {
				len = ((uint32_t)usb_ts_rand_noise()) % ((uint32_t)io_max);
			} else {
				len = io_max;
			}

			if (p->random_tx_delay) {
				dly = ((uint32_t)usb_ts_rand_noise()) % 16000U;
			} else {
				dly = 0;
			}

			if (p->loop_data != 0) {
				if (in_ready != 0) {
					len = libusb20_tr_get_length(p->xfer_in, 0);
					memcpy(out_buffer, in_buffer, len);
					in_ready = 0;
				} else {
					len = io_max + 1;
				}
				if (!libusb20_tr_pending(p->xfer_in)) {
					libusb20_tr_setup_bulk(p->xfer_in, in_buffer, io_max, 0);
					libusb20_tr_start(p->xfer_in);
					in_pending = 1;
				}
			} else {
				modem_write(out_buffer, len);
			}

			if (len <= io_max) {
				libusb20_tr_setup_bulk(p->xfer_out, out_buffer, len, 0);

				if (dly != 0)
					usleep(dly);

				libusb20_tr_start(p->xfer_out);

				out_pending = 1;
			}
		}
		libusb20_dev_wait_process(p->usb_dev, 500);

		if (libusb20_dev_check_connected(p->usb_dev) != 0) {
			printf("Device disconnected\n");
			break;
		}
	}

	libusb20_tr_stop(p->xfer_in);
	libusb20_tr_stop(p->xfer_out);

	printf("\nData stress test done!\n");

fail:
	if (in_buffer)
		free(in_buffer);
	if (out_buffer)
		free(out_buffer);
}