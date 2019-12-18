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
struct rsocket {int dummy; } ;
struct rs_svc_msg {int cmd; int /*<<< orphan*/  status; struct rsocket* rs; } ;
struct rs_svc {int /*<<< orphan*/ * sock; int /*<<< orphan*/  id; scalar_t__ cnt; int /*<<< orphan*/  run; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  EINVAL ; 
 int ERR (int) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mut ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rs_svc*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int rdma_seterrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_all (int /*<<< orphan*/ ,struct rs_svc_msg*,int) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_all (int /*<<< orphan*/ ,struct rs_svc_msg*,int) ; 

__attribute__((used)) static int rs_notify_svc(struct rs_svc *svc, struct rsocket *rs, int cmd)
{
	struct rs_svc_msg msg;
	int ret;

	pthread_mutex_lock(&mut);
	if (!svc->cnt) {
		ret = socketpair(AF_UNIX, SOCK_STREAM, 0, svc->sock);
		if (ret)
			goto unlock;

		ret = pthread_create(&svc->id, NULL, svc->run, svc);
		if (ret) {
			ret = ERR(ret);
			goto closepair;
		}
	}

	msg.cmd = cmd;
	msg.status = EINVAL;
	msg.rs = rs;
	write_all(svc->sock[0], &msg, sizeof msg);
	read_all(svc->sock[0], &msg, sizeof msg);
	ret = rdma_seterrno(msg.status);
	if (svc->cnt)
		goto unlock;

	pthread_join(svc->id, NULL);
closepair:
	close(svc->sock[0]);
	close(svc->sock[1]);
unlock:
	pthread_mutex_unlock(&mut);
	return ret;
}