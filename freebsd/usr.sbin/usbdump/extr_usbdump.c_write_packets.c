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
typedef  int uint8_t ;
struct usbcap {int /*<<< orphan*/  wfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int htole32 (int const) ; 
 int write (int /*<<< orphan*/ ,int const*,int const) ; 

__attribute__((used)) static void
write_packets(struct usbcap *p, const uint8_t *data, const int datalen)
{
	int len = htole32(datalen);
	int ret;

	ret = write(p->wfd, &len, sizeof(int));
	if (ret != sizeof(int)) {
		err(EXIT_FAILURE, "Could not write length "
		    "field of USB data payload");
	}
	ret = write(p->wfd, data, datalen);
	if (ret != datalen) {
		err(EXIT_FAILURE, "Could not write "
		    "complete USB data payload");
	}
}