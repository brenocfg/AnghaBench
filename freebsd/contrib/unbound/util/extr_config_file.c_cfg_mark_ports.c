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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int atoi (char const*) ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int 
cfg_mark_ports(const char* str, int allow, int* avail, int num)
{
	char* mid = strchr(str, '-');
	if(!mid) {
		int port = atoi(str);
		if(port == 0 && strcmp(str, "0") != 0) {
			log_err("cannot parse port number '%s'", str);
			return 0;
		}
		if(port < num)
			avail[port] = (allow?port:0);
	} else {
		int i, low, high = atoi(mid+1);
		char buf[16];
		if(high == 0 && strcmp(mid+1, "0") != 0) {
			log_err("cannot parse port number '%s'", mid+1);
			return 0;
		}
		if( (int)(mid-str)+1 >= (int)sizeof(buf) ) {
			log_err("cannot parse port number '%s'", str);
			return 0;
		}
		if(mid > str)
			memcpy(buf, str, (size_t)(mid-str));
		buf[mid-str] = 0;
		low = atoi(buf);
		if(low == 0 && strcmp(buf, "0") != 0) {
			log_err("cannot parse port number '%s'", buf);
			return 0;
		}
		for(i=low; i<=high; i++) {
			if(i < num)
				avail[i] = (allow?i:0);
		}
		return 1;
	}
	return 1;
}