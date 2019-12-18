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
typedef  int /*<<< orphan*/  xcb_xrm_database_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  ELOG (char*,...) ; 
 double HUGE_VAL ; 
 int /*<<< orphan*/ * conn ; 
 scalar_t__ dpi ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ init_dpi_fallback () ; 
 scalar_t__ lround (double) ; 
 double strtod (char*,char**) ; 
 int /*<<< orphan*/  xcb_xrm_database_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_xrm_database_from_default (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_xrm_resource_get_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char**) ; 

void init_dpi(void) {
    xcb_xrm_database_t *database = NULL;
    char *resource = NULL;

    if (conn == NULL) {
        goto init_dpi_end;
    }

    database = xcb_xrm_database_from_default(conn);
    if (database == NULL) {
        ELOG("Failed to open the resource database.\n");
        goto init_dpi_end;
    }

    xcb_xrm_resource_get_string(database, "Xft.dpi", NULL, &resource);
    if (resource == NULL) {
        DLOG("Resource Xft.dpi not specified, skipping.\n");
        goto init_dpi_end;
    }

    char *endptr;
    double in_dpi = strtod(resource, &endptr);
    if (in_dpi == HUGE_VAL || dpi < 0 || *endptr != '\0' || endptr == resource) {
        ELOG("Xft.dpi = %s is an invalid number and couldn't be parsed.\n", resource);
        dpi = 0;
        goto init_dpi_end;
    }
    dpi = lround(in_dpi);

    DLOG("Found Xft.dpi = %ld.\n", dpi);

init_dpi_end:
    free(resource);

    if (database != NULL) {
        xcb_xrm_database_free(database);
    }

    if (dpi == 0) {
        DLOG("Using fallback for calculating DPI.\n");
        dpi = init_dpi_fallback();
        DLOG("Using dpi = %ld\n", dpi);
    }
}