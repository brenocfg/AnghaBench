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
struct ucred {scalar_t__ cr_uid; } ;

/* Variables and functions */
 int EPERM ; 
#define  PRIV_ADJTIME 132 
#define  PRIV_CLOCK_SETTIME 131 
#define  PRIV_NETINET_RESERVEDPORT 130 
#define  PRIV_NETINET_REUSEPORT 129 
#define  PRIV_NTP_ADJTIME 128 
 scalar_t__ ntpd_enabled ; 
 scalar_t__ ntpd_uid ; 

__attribute__((used)) static int
ntpd_priv_grant(struct ucred *cred, int priv)
{

	if (ntpd_enabled && cred->cr_uid == ntpd_uid) {
		switch (priv) {
		case PRIV_ADJTIME:
		case PRIV_CLOCK_SETTIME:
		case PRIV_NTP_ADJTIME:
		case PRIV_NETINET_RESERVEDPORT:
		case PRIV_NETINET_REUSEPORT:
			return (0);
		default:
			break;
		}
	}
	return (EPERM);
}