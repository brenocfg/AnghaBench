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
struct dog_data {int stdin_fd; int stdout_fd; int* close_me; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  helper_wait (int) ; 
 int os_getpid () ; 
 int os_pipe (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pre_exec ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int read (int,char*,int) ; 
 int run_helper (int /*<<< orphan*/ ,struct dog_data*,char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int start_watchdog(int *in_fd_ret, int *out_fd_ret, char *sock)
{
	struct dog_data data;
	int in_fds[2], out_fds[2], pid, n, err;
	char pid_buf[sizeof("nnnnnnn\0")], c;
	char *pid_args[] = { "/usr/bin/uml_watchdog", "-pid", pid_buf, NULL };
	char *mconsole_args[] = { "/usr/bin/uml_watchdog", "-mconsole", NULL,
				  NULL };
	char **args = NULL;

	err = os_pipe(in_fds, 1, 0);
	if (err < 0) {
		printk("harddog_open - os_pipe failed, err = %d\n", -err);
		goto out;
	}

	err = os_pipe(out_fds, 1, 0);
	if (err < 0) {
		printk("harddog_open - os_pipe failed, err = %d\n", -err);
		goto out_close_in;
	}

	data.stdin_fd = out_fds[0];
	data.stdout_fd = in_fds[1];
	data.close_me[0] = out_fds[1];
	data.close_me[1] = in_fds[0];

	if (sock != NULL) {
		mconsole_args[2] = sock;
		args = mconsole_args;
	}
	else {
		/* XXX The os_getpid() is not SMP correct */
		sprintf(pid_buf, "%d", os_getpid());
		args = pid_args;
	}

	pid = run_helper(pre_exec, &data, args);

	close(out_fds[0]);
	close(in_fds[1]);

	if (pid < 0) {
		err = -pid;
		printk("harddog_open - run_helper failed, errno = %d\n", -err);
		goto out_close_out;
	}

	n = read(in_fds[0], &c, sizeof(c));
	if (n == 0) {
		printk("harddog_open - EOF on watchdog pipe\n");
		helper_wait(pid);
		err = -EIO;
		goto out_close_out;
	}
	else if (n < 0) {
		printk("harddog_open - read of watchdog pipe failed, "
		       "err = %d\n", errno);
		helper_wait(pid);
		err = n;
		goto out_close_out;
	}
	*in_fd_ret = in_fds[0];
	*out_fd_ret = out_fds[1];
	return 0;

 out_close_in:
	close(in_fds[0]);
	close(in_fds[1]);
 out_close_out:
	close(out_fds[0]);
	close(out_fds[1]);
 out:
	return err;
}