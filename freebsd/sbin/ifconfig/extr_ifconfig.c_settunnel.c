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
struct afswtch {int /*<<< orphan*/  (* af_settunnel ) (int,struct addrinfo*,struct addrinfo*) ;int /*<<< orphan*/  af_name; } ;
struct addrinfo {TYPE_1__* ai_addr; } ;
struct TYPE_2__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct addrinfo**) ; 
 int /*<<< orphan*/  stub1 (int,struct addrinfo*,struct addrinfo*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
settunnel(const char *src, const char *dst, int s, const struct afswtch *afp)
{
	struct addrinfo *srcres, *dstres;
	int ecode;

	if (afp->af_settunnel == NULL) {
		warn("address family %s does not support tunnel setup",
			afp->af_name);
		return;
	}

	if ((ecode = getaddrinfo(src, NULL, NULL, &srcres)) != 0)
		errx(1, "error in parsing address string: %s",
		    gai_strerror(ecode));

	if ((ecode = getaddrinfo(dst, NULL, NULL, &dstres)) != 0)
		errx(1, "error in parsing address string: %s",
		    gai_strerror(ecode));

	if (srcres->ai_addr->sa_family != dstres->ai_addr->sa_family)
		errx(1,
		    "source and destination address families do not match");

	afp->af_settunnel(s, srcres, dstres);

	freeaddrinfo(srcres);
	freeaddrinfo(dstres);
}