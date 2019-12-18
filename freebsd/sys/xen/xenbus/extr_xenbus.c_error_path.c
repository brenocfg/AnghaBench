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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  M_XENBUS ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* xenbus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
error_path(device_t dev)
{
	char *path_buffer = malloc(strlen("error/")
	    + strlen(xenbus_get_node(dev)) + 1,M_XENBUS, M_WAITOK);

	strcpy(path_buffer, "error/");
	strcpy(path_buffer + strlen("error/"), xenbus_get_node(dev));

	return (path_buffer);
}