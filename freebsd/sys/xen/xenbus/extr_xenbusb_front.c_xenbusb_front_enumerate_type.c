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
struct xenbusb_softc {int /*<<< orphan*/  xbs_node; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_XENSTORE ; 
 int /*<<< orphan*/  XST_NIL ; 
 struct xenbusb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbusb_add_device (int /*<<< orphan*/ ,char const*,char const*) ; 
 int xs_directory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,unsigned int*,char const***) ; 

__attribute__((used)) static int
xenbusb_front_enumerate_type(device_t dev, const char *type)
{
	struct xenbusb_softc *xbs;
	const char **dir;
	unsigned int i, count;
	int error;

	xbs = device_get_softc(dev);
	error = xs_directory(XST_NIL, xbs->xbs_node, type, &count, &dir);
	if (error)
		return (error);
	for (i = 0; i < count; i++)
		xenbusb_add_device(dev, type, dir[i]);

	free(dir, M_XENSTORE);

	return (0);
}