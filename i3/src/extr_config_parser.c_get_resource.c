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

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/ * conn ; 
 int /*<<< orphan*/ * database ; 
 int /*<<< orphan*/ * xcb_xrm_database_from_default (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_xrm_database_from_string (char*) ; 
 int /*<<< orphan*/  xcb_xrm_resource_get_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static char *get_resource(char *name) {
    if (conn == NULL) {
        return NULL;
    }

    /* Load the resource database lazily. */
    if (database == NULL) {
        database = xcb_xrm_database_from_default(conn);

        if (database == NULL) {
            ELOG("Failed to open the resource database.\n");

            /* Load an empty database so we don't keep trying to load the
             * default database over and over again. */
            database = xcb_xrm_database_from_string("");

            return NULL;
        }
    }

    char *resource;
    xcb_xrm_resource_get_string(database, name, NULL, &resource);
    return resource;
}