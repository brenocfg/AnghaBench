#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  enum snmp_tc { ____Placeholder_snmp_tc } snmp_tc ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/ * (* oct2tc ) (int,char*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int SNMP_UNKNOWN ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int,char*,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* text_convs ; 

char *
snmp_oct2tc(enum snmp_tc tc, uint32_t len, char *octets)
{
	uint32_t tc_len;
	char * buf;

	if (tc > SNMP_UNKNOWN)
		tc = SNMP_UNKNOWN;

	if (text_convs[tc].len > 0)
		tc_len = text_convs[tc].len;
	else
		tc_len = 2 * len + 3;

	if ((buf = malloc(tc_len)) == NULL ) {
		syslog(LOG_ERR, "malloc failed - %s", strerror(errno));
		return (NULL);
	}

	memset(buf, 0, tc_len);
	if (text_convs[tc].oct2tc(len, octets, buf) == NULL) {
		free(buf);
		return (NULL);
	}

	return (buf);
}