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
systrace_entry_setargdesc(int sysnum, int ndx, char *desc, size_t descsz)
{
	const char *p = NULL;
	switch (sysnum) {
	/* cloudabi_sys_clock_res_get */
	case 0:
		switch(ndx) {
		case 0:
			p = "cloudabi_clockid_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_clock_time_get */
	case 1:
		switch(ndx) {
		case 0:
			p = "cloudabi_clockid_t";
			break;
		case 1:
			p = "cloudabi_timestamp_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_condvar_signal */
	case 2:
		switch(ndx) {
		case 0:
			p = "userland cloudabi_condvar_t *";
			break;
		case 1:
			p = "cloudabi_scope_t";
			break;
		case 2:
			p = "cloudabi_nthreads_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_fd_close */
	case 3:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_fd_create1 */
	case 4:
		switch(ndx) {
		case 0:
			p = "cloudabi_filetype_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_fd_create2 */
	case 5:
		switch(ndx) {
		case 0:
			p = "cloudabi_filetype_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_fd_datasync */
	case 6:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_fd_dup */
	case 7:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi32_sys_fd_pread */
	case 8:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland const cloudabi32_iovec_t *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "cloudabi_filesize_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi32_sys_fd_pwrite */
	case 9:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland const cloudabi32_ciovec_t *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "cloudabi_filesize_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi32_sys_fd_read */
	case 10:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland const cloudabi32_iovec_t *";
			break;
		case 2:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_fd_replace */
	case 11:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "cloudabi_fd_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_fd_seek */
	case 12:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "cloudabi_filedelta_t";
			break;
		case 2:
			p = "cloudabi_whence_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_fd_stat_get */
	case 13:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland cloudabi_fdstat_t *";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_fd_stat_put */
	case 14:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland const cloudabi_fdstat_t *";
			break;
		case 2:
			p = "cloudabi_fdsflags_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_fd_sync */
	case 15:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi32_sys_fd_write */
	case 16:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland const cloudabi32_ciovec_t *";
			break;
		case 2:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_advise */
	case 17:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "cloudabi_filesize_t";
			break;
		case 2:
			p = "cloudabi_filesize_t";
			break;
		case 3:
			p = "cloudabi_advice_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_allocate */
	case 18:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "cloudabi_filesize_t";
			break;
		case 2:
			p = "cloudabi_filesize_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_create */
	case 19:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland const char *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "cloudabi_filetype_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_link */
	case 20:
		switch(ndx) {
		case 0:
			p = "cloudabi_lookup_t";
			break;
		case 1:
			p = "userland const char *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "cloudabi_fd_t";
			break;
		case 4:
			p = "userland const char *";
			break;
		case 5:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_open */
	case 21:
		switch(ndx) {
		case 0:
			p = "cloudabi_lookup_t";
			break;
		case 1:
			p = "userland const char *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "cloudabi_oflags_t";
			break;
		case 4:
			p = "userland const cloudabi_fdstat_t *";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_readdir */
	case 22:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland void *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "cloudabi_dircookie_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_readlink */
	case 23:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland const char *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "userland char *";
			break;
		case 4:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_rename */
	case 24:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland const char *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "cloudabi_fd_t";
			break;
		case 4:
			p = "userland const char *";
			break;
		case 5:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_stat_fget */
	case 25:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland cloudabi_filestat_t *";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_stat_fput */
	case 26:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland const cloudabi_filestat_t *";
			break;
		case 2:
			p = "cloudabi_fsflags_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_stat_get */
	case 27:
		switch(ndx) {
		case 0:
			p = "cloudabi_lookup_t";
			break;
		case 1:
			p = "userland const char *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "userland cloudabi_filestat_t *";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_stat_put */
	case 28:
		switch(ndx) {
		case 0:
			p = "cloudabi_lookup_t";
			break;
		case 1:
			p = "userland const char *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "userland const cloudabi_filestat_t *";
			break;
		case 4:
			p = "cloudabi_fsflags_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_symlink */
	case 29:
		switch(ndx) {
		case 0:
			p = "userland const char *";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "cloudabi_fd_t";
			break;
		case 3:
			p = "userland const char *";
			break;
		case 4:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_file_unlink */
	case 30:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland const char *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "cloudabi_ulflags_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_lock_unlock */
	case 31:
		switch(ndx) {
		case 0:
			p = "userland cloudabi_lock_t *";
			break;
		case 1:
			p = "cloudabi_scope_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_mem_advise */
	case 32:
		switch(ndx) {
		case 0:
			p = "userland void *";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "cloudabi_advice_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_mem_map */
	case 33:
		switch(ndx) {
		case 0:
			p = "userland void *";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "cloudabi_mprot_t";
			break;
		case 3:
			p = "cloudabi_mflags_t";
			break;
		case 4:
			p = "cloudabi_fd_t";
			break;
		case 5:
			p = "cloudabi_filesize_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_mem_protect */
	case 34:
		switch(ndx) {
		case 0:
			p = "userland void *";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "cloudabi_mprot_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_mem_sync */
	case 35:
		switch(ndx) {
		case 0:
			p = "userland void *";
			break;
		case 1:
			p = "size_t";
			break;
		case 2:
			p = "cloudabi_msflags_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_mem_unmap */
	case 36:
		switch(ndx) {
		case 0:
			p = "userland void *";
			break;
		case 1:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi32_sys_poll */
	case 37:
		switch(ndx) {
		case 0:
			p = "userland const cloudabi32_subscription_t *";
			break;
		case 1:
			p = "userland cloudabi_event_t *";
			break;
		case 2:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_proc_exec */
	case 38:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland const void *";
			break;
		case 2:
			p = "size_t";
			break;
		case 3:
			p = "userland const cloudabi_fd_t *";
			break;
		case 4:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_proc_exit */
	case 39:
		switch(ndx) {
		case 0:
			p = "cloudabi_exitcode_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_proc_fork */
	case 40:
		break;
	/* cloudabi_sys_proc_raise */
	case 41:
		switch(ndx) {
		case 0:
			p = "cloudabi_signal_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_random_get */
	case 42:
		switch(ndx) {
		case 0:
			p = "userland void *";
			break;
		case 1:
			p = "size_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi32_sys_sock_recv */
	case 43:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland const cloudabi32_recv_in_t *";
			break;
		case 2:
			p = "userland cloudabi32_recv_out_t *";
			break;
		default:
			break;
		};
		break;
	/* cloudabi32_sys_sock_send */
	case 44:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "userland const cloudabi32_send_in_t *";
			break;
		case 2:
			p = "userland cloudabi32_send_out_t *";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_sock_shutdown */
	case 45:
		switch(ndx) {
		case 0:
			p = "cloudabi_fd_t";
			break;
		case 1:
			p = "cloudabi_sdflags_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi32_sys_thread_create */
	case 46:
		switch(ndx) {
		case 0:
			p = "userland cloudabi32_threadattr_t *";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_thread_exit */
	case 47:
		switch(ndx) {
		case 0:
			p = "userland cloudabi_lock_t *";
			break;
		case 1:
			p = "cloudabi_scope_t";
			break;
		default:
			break;
		};
		break;
	/* cloudabi_sys_thread_yield */
	case 48:
		break;
	default:
		break;
	};
	if (p != NULL)
		strlcpy(desc, p, descsz);
}