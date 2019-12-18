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
struct xenbus_device_ivars {char* xd_otherend_path; int /*<<< orphan*/  xd_otherend_path_len; int /*<<< orphan*/  xd_otherend_id; int /*<<< orphan*/  xd_node; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_XENBUS ; 
 int /*<<< orphan*/  M_XENSTORE ; 
 int /*<<< orphan*/  XST_NIL ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* strdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int xs_gather (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xenbusb_front_get_otherend_node(device_t dev, struct xenbus_device_ivars *ivars)
{
	char *otherend_path;
	int error;

	if (ivars->xd_otherend_path != NULL) {
		free(ivars->xd_otherend_path, M_XENBUS);
		ivars->xd_otherend_path = NULL;
	}
		
	error = xs_gather(XST_NIL, ivars->xd_node,
	    "backend-id", "%i", &ivars->xd_otherend_id,
	    "backend", NULL, &otherend_path,
	    NULL);

	if (error == 0) {
		ivars->xd_otherend_path = strdup(otherend_path, M_XENBUS);
		ivars->xd_otherend_path_len = strlen(otherend_path);
		free(otherend_path, M_XENSTORE);
	}
	return (error);
}