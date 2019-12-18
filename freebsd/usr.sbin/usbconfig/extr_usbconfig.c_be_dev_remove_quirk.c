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
typedef  void* uint16_t ;
struct libusb20_quirk {int /*<<< orphan*/  quirkname; void* bcdDeviceHigh; void* bcdDeviceLow; void* pid; void* vid; } ;
struct libusb20_backend {int dummy; } ;
typedef  int /*<<< orphan*/  q ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int libusb20_be_remove_dev_quirk (struct libusb20_backend*,struct libusb20_quirk*) ; 
 int /*<<< orphan*/  memset (struct libusb20_quirk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
be_dev_remove_quirk(struct libusb20_backend *pbe,
    uint16_t vid, uint16_t pid, uint16_t lorev, uint16_t hirev,
    const char *str)
{
	struct libusb20_quirk q;
	int error;

	memset(&q, 0, sizeof(q));

	q.vid = vid;
	q.pid = pid;
	q.bcdDeviceLow = lorev;
	q.bcdDeviceHigh = hirev;
	strlcpy(q.quirkname, str, sizeof(q.quirkname));

	error = libusb20_be_remove_dev_quirk(pbe, &q);
	if (error) {
		fprintf(stderr, "Removing quirk '%s' failed, continuing.\n", str);
	}
	return;
}