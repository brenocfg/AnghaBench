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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int SOCK_CLOEXEC ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  acm_lock ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  htobe16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_port ; 
 int sock ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucma_set_server_port () ; 

void ucma_ib_init(void)
{
	struct sockaddr_in addr;
	static int init;
	int ret;

	if (init)
		return;

	pthread_mutex_lock(&acm_lock);
	if (init)
		goto unlock;

	if (!ucma_set_server_port())
		goto out;

	sock = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, IPPROTO_TCP);
	if (sock < 0)
		goto out;

	memset(&addr, 0, sizeof addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htobe32(INADDR_LOOPBACK);
	addr.sin_port = htobe16(server_port);
	ret = connect(sock, (struct sockaddr *) &addr, sizeof(addr));
	if (ret) {
		close(sock);
		sock = -1;
	}
out:
	init = 1;
unlock:
	pthread_mutex_unlock(&acm_lock);
}