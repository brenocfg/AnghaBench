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
typedef  int /*<<< orphan*/  tm ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf2native_int32 (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_serial_arithmitics_gmtime_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tm*) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

ldns_status
ldns_rdf2buffer_str_time(ldns_buffer *output, const ldns_rdf *rdf)
{
	/* create a YYYYMMDDHHMMSS string if possible */
	struct tm tm;
	char date_buf[16];

	memset(&tm, 0, sizeof(tm));
	if (ldns_serial_arithmitics_gmtime_r(ldns_rdf2native_int32(rdf), time(NULL), &tm)
	    && strftime(date_buf, 15, "%Y%m%d%H%M%S", &tm)) {
		ldns_buffer_printf(output, "%s", date_buf);
	}
	return ldns_buffer_status(output);
}