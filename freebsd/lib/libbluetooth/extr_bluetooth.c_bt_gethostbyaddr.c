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
struct hostent {int h_addrtype; int /*<<< orphan*/  h_addr; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int AF_BLUETOOTH ; 
 int /*<<< orphan*/  NO_RECOVERY ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  bt_endhostent () ; 
 struct hostent* bt_gethostent () ; 
 int /*<<< orphan*/  bt_sethostent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h_errno ; 
 int /*<<< orphan*/  host_stayopen ; 

struct hostent *
bt_gethostbyaddr(char const *addr, int len, int type)
{
	struct hostent	*p;

	if (type != AF_BLUETOOTH || len != sizeof(bdaddr_t)) {
		h_errno = NO_RECOVERY;
		return (NULL);
	}

	bt_sethostent(host_stayopen);
	while ((p = bt_gethostent()) != NULL)
		if (p->h_addrtype == type && bcmp(p->h_addr, addr, len) == 0)
			break;
	bt_endhostent();

	return (p);
}