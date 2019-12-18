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
struct libusb_device {struct libusb20_device* os_priv; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  tr_head; } ;
struct libusb20_device {struct libusb_device* privLuData; } ;
struct libusb20_backend {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  libusb_device ;
typedef  int /*<<< orphan*/  libusb_context ;

/* Variables and functions */
 int /*<<< orphan*/ * GET_CONTEXT (int /*<<< orphan*/ *) ; 
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int LIBUSB_ERROR_NO_MEM ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 struct libusb20_backend* libusb20_be_alloc_default () ; 
 int /*<<< orphan*/  libusb20_be_dequeue_device (struct libusb20_backend*,struct libusb20_device*) ; 
 struct libusb20_device* libusb20_be_device_foreach (struct libusb20_backend*,struct libusb20_device*) ; 
 int /*<<< orphan*/  libusb20_be_free (struct libusb20_backend*) ; 
 int /*<<< orphan*/ * libusb_ref_device (struct libusb_device*) ; 
 int /*<<< orphan*/  libusb_unref_device (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (struct libusb_device*,int /*<<< orphan*/ ,int) ; 

ssize_t
libusb_get_device_list(libusb_context *ctx, libusb_device ***list)
{
	struct libusb20_backend *usb_backend;
	struct libusb20_device *pdev;
	struct libusb_device *dev;
	int i;

	ctx = GET_CONTEXT(ctx);

	if (ctx == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	if (list == NULL)
		return (LIBUSB_ERROR_INVALID_PARAM);

	usb_backend = libusb20_be_alloc_default();
	if (usb_backend == NULL)
		return (LIBUSB_ERROR_NO_MEM);

	/* figure out how many USB devices are present */
	pdev = NULL;
	i = 0;
	while ((pdev = libusb20_be_device_foreach(usb_backend, pdev)))
		i++;

	/* allocate device pointer list */
	*list = malloc((i + 1) * sizeof(void *));
	if (*list == NULL) {
		libusb20_be_free(usb_backend);
		return (LIBUSB_ERROR_NO_MEM);
	}
	/* create libusb v1.0 compliant devices */
	i = 0;
	while ((pdev = libusb20_be_device_foreach(usb_backend, NULL))) {

		dev = malloc(sizeof(*dev));
		if (dev == NULL) {
			while (i != 0) {
				libusb_unref_device((*list)[i - 1]);
				i--;
			}
			free(*list);
			*list = NULL;
			libusb20_be_free(usb_backend);
			return (LIBUSB_ERROR_NO_MEM);
		}
		/* get device into libUSB v1.0 list */
		libusb20_be_dequeue_device(usb_backend, pdev);

		memset(dev, 0, sizeof(*dev));

		/* init transfer queues */
		TAILQ_INIT(&dev->tr_head);

		/* set context we belong to */
		dev->ctx = ctx;

		/* link together the two structures */
		dev->os_priv = pdev;
		pdev->privLuData = dev;

		(*list)[i] = libusb_ref_device(dev);
		i++;
	}
	(*list)[i] = NULL;

	libusb20_be_free(usb_backend);
	return (i);
}