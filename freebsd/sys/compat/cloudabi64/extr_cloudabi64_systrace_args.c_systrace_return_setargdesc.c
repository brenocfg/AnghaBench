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

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void
systrace_return_setargdesc(int sysnum, int ndx, char *desc, size_t descsz)
{
	const char *p = NULL;
	switch (sysnum) {
	/* cloudabi_sys_clock_res_get */
	case 0:
		if (ndx == 0 || ndx == 1)
			p = "cloudabi_timestamp_t";
		break;
	/* cloudabi_sys_clock_time_get */
	case 1:
		if (ndx == 0 || ndx == 1)
			p = "cloudabi_timestamp_t";
		break;
	/* cloudabi_sys_condvar_signal */
	case 2:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_fd_close */
	case 3:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_fd_create1 */
	case 4:
		if (ndx == 0 || ndx == 1)
			p = "cloudabi_fd_t";
		break;
	/* cloudabi_sys_fd_create2 */
	case 5:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_fd_datasync */
	case 6:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_fd_dup */
	case 7:
		if (ndx == 0 || ndx == 1)
			p = "cloudabi_fd_t";
		break;
	/* cloudabi64_sys_fd_pread */
	case 8:
		if (ndx == 0 || ndx == 1)
			p = "size_t";
		break;
	/* cloudabi64_sys_fd_pwrite */
	case 9:
		if (ndx == 0 || ndx == 1)
			p = "size_t";
		break;
	/* cloudabi64_sys_fd_read */
	case 10:
		if (ndx == 0 || ndx == 1)
			p = "size_t";
		break;
	/* cloudabi_sys_fd_replace */
	case 11:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_fd_seek */
	case 12:
		if (ndx == 0 || ndx == 1)
			p = "cloudabi_filesize_t";
		break;
	/* cloudabi_sys_fd_stat_get */
	case 13:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_fd_stat_put */
	case 14:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_fd_sync */
	case 15:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi64_sys_fd_write */
	case 16:
		if (ndx == 0 || ndx == 1)
			p = "size_t";
		break;
	/* cloudabi_sys_file_advise */
	case 17:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_file_allocate */
	case 18:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_file_create */
	case 19:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_file_link */
	case 20:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_file_open */
	case 21:
		if (ndx == 0 || ndx == 1)
			p = "cloudabi_fd_t";
		break;
	/* cloudabi_sys_file_readdir */
	case 22:
		if (ndx == 0 || ndx == 1)
			p = "size_t";
		break;
	/* cloudabi_sys_file_readlink */
	case 23:
		if (ndx == 0 || ndx == 1)
			p = "size_t";
		break;
	/* cloudabi_sys_file_rename */
	case 24:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_file_stat_fget */
	case 25:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_file_stat_fput */
	case 26:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_file_stat_get */
	case 27:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_file_stat_put */
	case 28:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_file_symlink */
	case 29:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_file_unlink */
	case 30:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_lock_unlock */
	case 31:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_mem_advise */
	case 32:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_mem_map */
	case 33:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_mem_protect */
	case 34:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_mem_sync */
	case 35:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_mem_unmap */
	case 36:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi64_sys_poll */
	case 37:
		if (ndx == 0 || ndx == 1)
			p = "size_t";
		break;
	/* cloudabi_sys_proc_exec */
	case 38:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_proc_exit */
	case 39:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_proc_fork */
	case 40:
	/* cloudabi_sys_proc_raise */
	case 41:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_random_get */
	case 42:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi64_sys_sock_recv */
	case 43:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi64_sys_sock_send */
	case 44:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_sock_shutdown */
	case 45:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi64_sys_thread_create */
	case 46:
		if (ndx == 0 || ndx == 1)
			p = "cloudabi_tid_t";
		break;
	/* cloudabi_sys_thread_exit */
	case 47:
		if (ndx == 0 || ndx == 1)
			p = "void";
		break;
	/* cloudabi_sys_thread_yield */
	case 48:
	default:
		break;
	};
	if (p != NULL)
		strlcpy(desc, p, descsz);
}