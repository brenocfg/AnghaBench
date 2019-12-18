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
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  scalar_t__ (* socket_fun ) (int,struct sockaddr const*,int) ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_ERRNO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  ENOTCAPABLE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ cap_rights_limit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cap_rights_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_3(socket_fun f, int s, const struct sockaddr_in *name,
    cap_rights_t *rights, cap_rights_t *sub_rights)
{

	ATF_REQUIRE((s = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
	ATF_REQUIRE(cap_rights_limit(s, rights) >= 0);
	ATF_REQUIRE_ERRNO(EAFNOSUPPORT,
	    f(s, (const struct sockaddr *)name,
	        sizeof(struct sockaddr_in)) < 0);
	ATF_REQUIRE(cap_rights_limit(s,
	                cap_rights_remove(rights, sub_rights)) >= 0);
	ATF_REQUIRE_ERRNO(ENOTCAPABLE,
	    f(s, (const struct sockaddr *)name,
	        sizeof(struct sockaddr_in)) < 0);
}