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
struct libusb20_backend_methods {int /*<<< orphan*/  (* init_backend ) (struct libusb20_backend*) ;} ;
struct libusb20_backend {struct libusb20_backend_methods const* methods; int /*<<< orphan*/  usb_devs; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct libusb20_backend* malloc (int) ; 
 int /*<<< orphan*/  memset (struct libusb20_backend*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct libusb20_backend*) ; 

struct libusb20_backend *
libusb20_be_alloc(const struct libusb20_backend_methods *methods)
{
	struct libusb20_backend *pbe;

	pbe = malloc(sizeof(*pbe));
	if (pbe == NULL) {
		return (NULL);
	}
	memset(pbe, 0, sizeof(*pbe));

	TAILQ_INIT(&(pbe->usb_devs));

	pbe->methods = methods;		/* set backend methods */

	/* do the initial device scan */
	if (pbe->methods->init_backend) {
		pbe->methods->init_backend(pbe);
	}
	return (pbe);
}