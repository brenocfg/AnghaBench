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
typedef  int /*<<< orphan*/  xs_watch_cb_t ;
struct xs_watch {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  M_XENBUS ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int xenbus_watch_path (int /*<<< orphan*/ ,char*,struct xs_watch*,int /*<<< orphan*/ *,uintptr_t) ; 

int
xenbus_watch_path2(device_t dev, const char *path,
    const char *path2, struct xs_watch *watch, 
    xs_watch_cb_t *callback, uintptr_t callback_data)
{
	int error;
	char *state = malloc(strlen(path) + 1 + strlen(path2) + 1,
	   M_XENBUS, M_WAITOK);

	strcpy(state, path);
	strcat(state, "/");
	strcat(state, path2);

	error = xenbus_watch_path(dev, state, watch, callback, callback_data);
	if (error) {
		free(state,M_XENBUS);
	}

	return (error);
}