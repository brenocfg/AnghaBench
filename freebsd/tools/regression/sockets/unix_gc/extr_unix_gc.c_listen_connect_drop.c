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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  close3 (int,int,int) ; 
 int /*<<< orphan*/  my_bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  my_connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  my_getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  my_listen (int,int) ; 
 int my_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_socketpair (int*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  save_sysctls (int*,int*) ; 
 int /*<<< orphan*/  sendfd (int,int) ; 
 int /*<<< orphan*/  setnonblock (int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 char* test ; 
 int /*<<< orphan*/  test_sysctls (int,int) ; 

__attribute__((used)) static void
listen_connect_drop(void)
{
	struct sockaddr_in sin;
	int slisten, sconnect, sv[2];
	int inflight, openfiles;
	socklen_t len;

	test = "listen_connect_drop";
	printf("%s\n", test);
	save_sysctls(&inflight, &openfiles);

	slisten = my_socket(PF_INET, SOCK_STREAM, 0);
	my_bind(slisten, (struct sockaddr *)&sin, sizeof(sin));
	my_listen(slisten, -1);

	my_socketpair(sv);

	len = sizeof(sin);
	my_getsockname(slisten, (struct sockaddr *)&sin, &len);

	sconnect = my_socket(PF_INET, SOCK_STREAM, 0);
	setnonblock(sconnect);
	my_connect(sconnect, (struct sockaddr *)&sin, len);

	sleep(1);
	sendfd(sv[0], slisten);
	close3(slisten, sv[0], sv[1]);
	sleep(1);
	close(sconnect);

	test_sysctls(inflight, openfiles);
}