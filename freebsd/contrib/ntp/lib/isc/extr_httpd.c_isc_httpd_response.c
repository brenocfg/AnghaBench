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
struct TYPE_4__ {char* protocol; char* retmsg; int retcode; int /*<<< orphan*/  headerbuffer; } ;
typedef  TYPE_1__ isc_httpd_t ;

/* Variables and functions */
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ grow_headerspace (TYPE_1__*) ; 
 int /*<<< orphan*/  isc_buffer_add (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int isc_buffer_availablelength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_buffer_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int,char*) ; 
 int strlen (char*) ; 

isc_result_t
isc_httpd_response(isc_httpd_t *httpd)
{
	isc_result_t result;
	unsigned int needlen;

	needlen = strlen(httpd->protocol) + 1; /* protocol + space */
	needlen += 3 + 1;  /* room for response code, always 3 bytes */
	needlen += strlen(httpd->retmsg) + 2;  /* return msg + CRLF */

	while (isc_buffer_availablelength(&httpd->headerbuffer) < needlen) {
		result = grow_headerspace(httpd);
		if (result != ISC_R_SUCCESS)
			return (result);
	}

	sprintf(isc_buffer_used(&httpd->headerbuffer), "%s %03d %s\r\n",
		httpd->protocol, httpd->retcode, httpd->retmsg);
	isc_buffer_add(&httpd->headerbuffer, needlen);

	return (ISC_R_SUCCESS);
}