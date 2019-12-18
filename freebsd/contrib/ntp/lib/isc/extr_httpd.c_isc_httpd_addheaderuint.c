#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
struct TYPE_4__ {int /*<<< orphan*/  headerbuffer; } ;
typedef  TYPE_1__ isc_httpd_t ;

/* Variables and functions */
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ grow_headerspace (TYPE_1__*) ; 
 int /*<<< orphan*/  isc_buffer_add (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int isc_buffer_availablelength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_buffer_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 unsigned int strlen (char const*) ; 

isc_result_t
isc_httpd_addheaderuint(isc_httpd_t *httpd, const char *name, int val) {
	isc_result_t result;
	unsigned int needlen;
	char buf[sizeof "18446744073709551616"];

	sprintf(buf, "%d", val);

	needlen = strlen(name); /* name itself */
	needlen += 2 + strlen(buf); /* :<space> and val */
	needlen += 2; /* CRLF */

	while (isc_buffer_availablelength(&httpd->headerbuffer) < needlen) {
		result = grow_headerspace(httpd);
		if (result != ISC_R_SUCCESS)
			return (result);
	}

	sprintf(isc_buffer_used(&httpd->headerbuffer),
		"%s: %s\r\n", name, buf);

	isc_buffer_add(&httpd->headerbuffer, needlen);

	return (ISC_R_SUCCESS);
}