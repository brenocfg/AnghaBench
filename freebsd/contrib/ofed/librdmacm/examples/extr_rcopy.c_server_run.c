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
union rsocket_address {int /*<<< orphan*/  sa; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_RDWR ; 
 char* _ntop (union rsocket_address*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int raccept (int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  rclose (int) ; 
 int /*<<< orphan*/  rshutdown (int,int /*<<< orphan*/ ) ; 
 int server_listen () ; 
 int /*<<< orphan*/  server_process (int) ; 

__attribute__((used)) static int server_run(void)
{
	int lrs, rs;
	union rsocket_address rsa;
	socklen_t len;

	lrs = server_listen();
	if (lrs < 0)
		return lrs;

	while (1) {
		len = sizeof rsa;
		printf("waiting for connection...");
		fflush(NULL);
		rs = raccept(lrs, &rsa.sa, &len);

		printf("client: %s\n", _ntop(&rsa));
		server_process(rs);

		rshutdown(rs, SHUT_RDWR);
		rclose(rs);
	}
	return 0;
}