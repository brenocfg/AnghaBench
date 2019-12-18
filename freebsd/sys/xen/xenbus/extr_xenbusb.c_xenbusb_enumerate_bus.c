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
typedef  size_t u_int ;
struct xenbusb_softc {int /*<<< orphan*/  xbs_dev; int /*<<< orphan*/  xbs_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_XENSTORE ; 
 int /*<<< orphan*/  XENBUSB_ENUMERATE_TYPE (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  XST_NIL ; 
 int /*<<< orphan*/  free (char const**,int /*<<< orphan*/ ) ; 
 int xs_directory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t*,char const***) ; 

__attribute__((used)) static int
xenbusb_enumerate_bus(struct xenbusb_softc *xbs)
{
	const char **types;
	u_int type_idx;
	u_int type_count;
	int error;

	error = xs_directory(XST_NIL, xbs->xbs_node, "", &type_count, &types);
	if (error)
		return (error);

	for (type_idx = 0; type_idx < type_count; type_idx++)
		XENBUSB_ENUMERATE_TYPE(xbs->xbs_dev, types[type_idx]);

	free(types, M_XENSTORE);

	return (0);
}