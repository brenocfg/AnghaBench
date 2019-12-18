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
#define  DNS_ERR_CANCEL 139 
#define  DNS_ERR_FORMAT 138 
#define  DNS_ERR_NODATA 137 
#define  DNS_ERR_NONE 136 
#define  DNS_ERR_NOTEXIST 135 
#define  DNS_ERR_NOTIMPL 134 
#define  DNS_ERR_REFUSED 133 
#define  DNS_ERR_SERVERFAILED 132 
#define  DNS_ERR_SHUTDOWN 131 
#define  DNS_ERR_TIMEOUT 130 
#define  DNS_ERR_TRUNCATED 129 
#define  DNS_ERR_UNKNOWN 128 

const char *
evdns_err_to_string(int err)
{
    switch (err) {
	case DNS_ERR_NONE: return "no error";
	case DNS_ERR_FORMAT: return "misformatted query";
	case DNS_ERR_SERVERFAILED: return "server failed";
	case DNS_ERR_NOTEXIST: return "name does not exist";
	case DNS_ERR_NOTIMPL: return "query not implemented";
	case DNS_ERR_REFUSED: return "refused";

	case DNS_ERR_TRUNCATED: return "reply truncated or ill-formed";
	case DNS_ERR_UNKNOWN: return "unknown";
	case DNS_ERR_TIMEOUT: return "request timed out";
	case DNS_ERR_SHUTDOWN: return "dns subsystem shut down";
	case DNS_ERR_CANCEL: return "dns request canceled";
	case DNS_ERR_NODATA: return "no records in the reply";
	default: return "[Unknown error code]";
    }
}