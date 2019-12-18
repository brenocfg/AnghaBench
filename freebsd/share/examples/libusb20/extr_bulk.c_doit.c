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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct libusb20_transfer {int dummy; } ;
struct libusb20_device {int dummy; } ;

/* Variables and functions */
 int BUFLEN ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  in_ep ; 
 int /*<<< orphan*/  libusb20_dev_close (struct libusb20_device*) ; 
 int libusb20_dev_open (struct libusb20_device*,int) ; 
 int libusb20_dev_set_config_index (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 char* libusb20_strerror (int) ; 
 int libusb20_tr_bulk_intr_sync (struct libusb20_transfer*,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb20_tr_close (struct libusb20_transfer*) ; 
 struct libusb20_transfer* libusb20_tr_get_pointer (struct libusb20_device*,int) ; 
 int libusb20_tr_open (struct libusb20_transfer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * out_buf ; 
 int /*<<< orphan*/  out_ep ; 
 scalar_t__ out_len ; 
 int /*<<< orphan*/  print_formatted (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
doit(struct libusb20_device *dev)
{
  int rv;

  /*
   * Open the device, allocating memory for two possible (bulk or
   * interrupt) transfers.
   *
   * If only control transfers are intended (via
   * libusb20_dev_request_sync()), transfer_max can be given as 0.
   */
  if ((rv = libusb20_dev_open(dev, 2)) != 0)
    {
      fprintf(stderr, "libusb20_dev_open: %s\n", libusb20_strerror(rv));
      return;
    }

  /*
   * If the device has more than one configuration, select the desired
   * one here.
   */
  if ((rv = libusb20_dev_set_config_index(dev, 0)) != 0)
    {
      fprintf(stderr, "libusb20_dev_set_config_index: %s\n", libusb20_strerror(rv));
      return;
    }

  /*
   * Two transfers have been requested in libusb20_dev_open() above;
   * obtain the corresponding transfer struct pointers.
   */
  struct libusb20_transfer *xfr_out = libusb20_tr_get_pointer(dev, 0);
  struct libusb20_transfer *xfr_in = libusb20_tr_get_pointer(dev, 1);

  if (xfr_in == NULL || xfr_out == NULL)
    {
      fprintf(stderr, "libusb20_tr_get_pointer: %s\n", libusb20_strerror(rv));
      return;
    }

  /*
   * Open both transfers, the "out" one for the write endpoint, the
   * "in" one for the read endpoint (ep | 0x80).
   */
  if ((rv = libusb20_tr_open(xfr_out, 0, 1, out_ep)) != 0)
    {
      fprintf(stderr, "libusb20_tr_open: %s\n", libusb20_strerror(rv));
      return;
    }
  if ((rv = libusb20_tr_open(xfr_in, 0, 1, in_ep)) != 0)
    {
      fprintf(stderr, "libusb20_tr_open: %s\n", libusb20_strerror(rv));
      return;
    }

  uint8_t in_buf[BUFLEN];
  uint32_t rlen;

  if (out_len > 0)
    {
      if ((rv = libusb20_tr_bulk_intr_sync(xfr_out, out_buf, out_len, &rlen, TIMEOUT))
	  != 0)
	{
	  fprintf(stderr, "libusb20_tr_bulk_intr_sync (OUT): %s\n", libusb20_strerror(rv));
	}
      printf("sent %d bytes\n", rlen);
    }

  if ((rv = libusb20_tr_bulk_intr_sync(xfr_in, in_buf, BUFLEN, &rlen, TIMEOUT))
      != 0)
    {
      fprintf(stderr, "libusb20_tr_bulk_intr_sync: %s\n", libusb20_strerror(rv));
    }
      printf("received %d bytes\n", rlen);
      if (rlen > 0)
	print_formatted(in_buf, rlen);

  libusb20_tr_close(xfr_out);
  libusb20_tr_close(xfr_in);

  libusb20_dev_close(dev);
}