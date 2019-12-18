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
struct hostent {int dummy; } ;
struct hostdata {int /*<<< orphan*/  data; int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 struct hostdata* __hostdata_init () ; 
 scalar_t__ gethostbyaddr_r (void const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct hostent**,int*) ; 

struct hostent *
gethostbyaddr(const void *addr, socklen_t len, int af)
{
	struct hostdata *hd;
	struct hostent *rval;
	int ret_h_errno;

	if ((hd = __hostdata_init()) == NULL)
		return (NULL);
	if (gethostbyaddr_r(addr, len, af, &hd->host, hd->data,
	    sizeof(hd->data), &rval, &ret_h_errno) != 0)
		return (NULL);
	return (rval);
}