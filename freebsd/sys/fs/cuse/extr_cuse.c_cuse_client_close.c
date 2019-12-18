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
struct thread {int dummy; } ;
struct cuse_client_command {int dummy; } ;
struct cuse_client {int /*<<< orphan*/  fflags; struct cuse_client_command* cmds; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 size_t CUSE_CMD_CLOSE ; 
 int cuse_client_get (struct cuse_client**) ; 
 int /*<<< orphan*/  cuse_client_is_closing (struct cuse_client*) ; 
 int cuse_client_receive_command_locked (struct cuse_client_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuse_client_send_command_locked (struct cuse_client_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuse_cmd_lock (struct cuse_client_command*) ; 
 int /*<<< orphan*/  cuse_cmd_unlock (struct cuse_client_command*) ; 
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_unlock () ; 

__attribute__((used)) static int
cuse_client_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
	struct cuse_client_command *pccmd;
	struct cuse_client *pcc;
	int error;

	error = cuse_client_get(&pcc);
	if (error != 0)
		return (0);

	pccmd = &pcc->cmds[CUSE_CMD_CLOSE];

	cuse_cmd_lock(pccmd);

	cuse_lock();
	cuse_client_send_command_locked(pccmd, 0, 0, pcc->fflags, 0);

	error = cuse_client_receive_command_locked(pccmd, 0, 0);
	cuse_unlock();

	cuse_cmd_unlock(pccmd);

	cuse_lock();
	cuse_client_is_closing(pcc);
	cuse_unlock();

	return (0);
}