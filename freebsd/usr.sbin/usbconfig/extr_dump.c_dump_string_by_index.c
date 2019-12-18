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
typedef  scalar_t__ uint8_t ;
struct libusb20_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ libusb20_dev_req_string_simple_sync (struct libusb20_device*,scalar_t__,char*,int) ; 
 scalar_t__ libusb20_dev_req_string_sync (struct libusb20_device*,scalar_t__,int /*<<< orphan*/ ,char*,int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
dump_string_by_index(struct libusb20_device *pdev, uint8_t str_index)
{
	char *pbuf;
	uint8_t n;
	uint8_t len;

	pbuf = malloc(256);
	if (pbuf == NULL)
		err(1, "out of memory");

	if (str_index == 0) {
		/* language table */
		if (libusb20_dev_req_string_sync(pdev,
		    str_index, 0, pbuf, 256)) {
			printf("STRING_0x%02x = <read error>\n", str_index);
		} else {
			printf("STRING_0x%02x = ", str_index);
			len = (uint8_t)pbuf[0];
			for (n = 0; n != len; n++) {
				printf("0x%02x%s", (uint8_t)pbuf[n],
				    (n != (len - 1)) ? ", " : "");
			}
			printf("\n");
		}
	} else {
		/* ordinary string */
		if (libusb20_dev_req_string_simple_sync(pdev,
		    str_index, pbuf, 256)) {
			printf("STRING_0x%02x = <read error>\n", str_index);
		} else {
			printf("STRING_0x%02x = <%s>\n", str_index, pbuf);
		}
	}
	free(pbuf);
}