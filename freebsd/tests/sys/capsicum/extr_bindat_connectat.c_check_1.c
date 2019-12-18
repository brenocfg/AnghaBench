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

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_ERRNO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_1(socket_fun f, int s, const struct sockaddr_in *name)
{

	ATF_REQUIRE((s = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
	ATF_REQUIRE_ERRNO(EAFNOSUPPORT,
	    f(s, (const struct sockaddr *)(name),
	        sizeof(struct sockaddr_in)) < 0);
}