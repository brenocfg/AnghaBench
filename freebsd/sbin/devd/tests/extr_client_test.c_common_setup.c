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
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  devd_addr ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SUN_LEN (struct sockaddr_un*) ; 
 int connect (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_two_events () ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
common_setup(int socktype, const char* sockpath) {
	struct sockaddr_un devd_addr;
	int s, error;

	memset(&devd_addr, 0, sizeof(devd_addr));
	devd_addr.sun_family = PF_LOCAL;
	strlcpy(devd_addr.sun_path, sockpath, sizeof(devd_addr.sun_path));
	s = socket(PF_LOCAL, socktype, 0);
	ATF_REQUIRE(s >= 0);
	error = connect(s, (struct sockaddr*)&devd_addr, SUN_LEN(&devd_addr));
	ATF_REQUIRE_EQ(0, error);

	create_two_events();
	return (s);
}