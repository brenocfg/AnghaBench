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
typedef  int /*<<< orphan*/  sun ;
struct sockaddr_un {int sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  bzero (struct sockaddr_un*,int) ; 
 int /*<<< orphan*/  close3 (int,int,int) ; 
 char* dpath ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  my_listen (int,int) ; 
 int my_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_socketpair (int*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  save_sysctls (int*,int*) ; 
 int /*<<< orphan*/  sendfd (int,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 char* test ; 
 int /*<<< orphan*/  test_sysctls (int,int) ; 

__attribute__((used)) static void
listen_drop(void)
{
	struct sockaddr_un sun;
	struct sockaddr_in sin;
	int inflight, openfiles;
	int s, sv[2];

	bzero(&sun, sizeof(sun));
	sun.sun_family = AF_LOCAL;
	sun.sun_len = sizeof(sun);

	/*
	 * Close listen socket first.
	 */
	test = "listen_drop_unp1";
	printf("%s\n", test);
	snprintf(sun.sun_path, sizeof(sun.sun_path), "%s/%s", dpath, test);
	save_sysctls(&inflight, &openfiles);
	s = my_socket(PF_LOCAL, SOCK_STREAM, 0);
	my_bind(s, (struct sockaddr *)&sun, sizeof(sun));
	my_listen(s, -1);
	my_socketpair(sv);
	sendfd(sv[0], s);
	close3(s, sv[0], sv[1]);
	test_sysctls(inflight, openfiles);

	/*
	 * Close socketpair first.
	 */
	test = "listen_drop_unp2";
	printf("%s\n", test);
	snprintf(sun.sun_path, sizeof(sun.sun_path), "%s/%s", dpath, test);
	save_sysctls(&inflight, &openfiles);
	s = my_socket(PF_LOCAL, SOCK_STREAM, 0);
	my_bind(s, (struct sockaddr *)&sun, sizeof(sun));
	my_listen(s, -1);
	my_socketpair(sv);
	sendfd(sv[0], s);
	close3(sv[0], sv[1], s);
	test_sysctls(inflight, openfiles);

	sin.sin_family = AF_INET;
	sin.sin_len = sizeof(sin);
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sin.sin_port = htons(0);

	/*
	 * Close listen socket first.
	 */
	test = "listen_drop_inet1";
	printf("%s\n", test);
	bzero(&sun, sizeof(sun));
	save_sysctls(&inflight, &openfiles);
	s = my_socket(PF_INET, SOCK_STREAM, 0);
	my_bind(s, (struct sockaddr *)&sin, sizeof(sin));
	my_listen(s, -1);
	my_socketpair(sv);
	sendfd(sv[0], s);
	close3(s, sv[0], sv[1]);
	test_sysctls(inflight, openfiles);

	/*
	 * Close socketpair first.
	 */
	test = "listen_drop_inet2";
	printf("%s\n", test);
	bzero(&sun, sizeof(sun));
	save_sysctls(&inflight, &openfiles);
	s = my_socket(PF_INET, SOCK_STREAM, 0);
	my_bind(s, (struct sockaddr *)&sin, sizeof(sin));
	my_listen(s, -1);
	my_socketpair(sv);
	sendfd(sv[0], s);
	close3(sv[0], sv[1], s);
	test_sysctls(inflight, openfiles);
}