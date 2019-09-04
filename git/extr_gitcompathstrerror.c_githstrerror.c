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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
#define  HOST_NOT_FOUND 131 
#define  NO_DATA 130 
#define  NO_RECOVERY 129 
#define  TRY_AGAIN 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

const char *githstrerror(int err)
{
	static char buffer[48];
	switch (err)
	{
	case HOST_NOT_FOUND:
		return "Authoritative answer: host not found";
	case NO_DATA:
		return "Valid name, no data record of requested type";
	case NO_RECOVERY:
		return "Non recoverable errors, FORMERR, REFUSED, NOTIMP";
	case TRY_AGAIN:
		return "Non-authoritative \"host not found\", or SERVERFAIL";
	}
	snprintf(buffer, sizeof(buffer), "Name resolution error %d", err);
	return buffer;
}