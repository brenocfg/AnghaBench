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
typedef  int /*<<< orphan*/  val ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCAL_CREDS ; 
 int /*<<< orphan*/  errno ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
localcreds(int sockfd)
{
	socklen_t sz;
	int rc, val;

	sz = sizeof(val);
	rc = getsockopt(sockfd, 0, LOCAL_CREDS, &val, &sz);
	ATF_REQUIRE_MSG(rc != -1, "getsockopt(LOCAL_CREDS) failed: %s",
	    strerror(errno));
	return (val != 0);
}