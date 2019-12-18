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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  tm ;
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sldns_read_uint32 (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_serial_arithmetics_gmtime_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tm*) ; 
 int sldns_str_print (char**,size_t*,char*,char*) ; 
 scalar_t__ strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int sldns_wire2str_time_scan(uint8_t** d, size_t* dl, char** s, size_t* sl)
{
	/* create a YYYYMMDDHHMMSS string if possible */
	struct tm tm;
	char date_buf[16];
	uint32_t t;
	memset(&tm, 0, sizeof(tm));
	if(*dl < 4) return -1;
	t = sldns_read_uint32(*d);
	date_buf[15]=0;
	if(sldns_serial_arithmetics_gmtime_r(t, time(NULL), &tm) &&
		strftime(date_buf, 15, "%Y%m%d%H%M%S", &tm)) {
		(*d) += 4;
		(*dl) -= 4;
		return sldns_str_print(s, sl, "%s", date_buf);
	}
	return -1;
}