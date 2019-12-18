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
struct ucred {int /*<<< orphan*/  cr_label; } ;
struct mac_biba {int dummy; } ;

/* Variables and functions */
#define  PRIV_AUDIT_GETAUDIT 205 
#define  PRIV_AUDIT_SETAUDIT 204 
#define  PRIV_AUDIT_SUBMIT 203 
#define  PRIV_CRED_SETEGID 202 
#define  PRIV_CRED_SETEUID 201 
#define  PRIV_CRED_SETGID 200 
#define  PRIV_CRED_SETGROUPS 199 
#define  PRIV_CRED_SETREGID 198 
#define  PRIV_CRED_SETRESGID 197 
#define  PRIV_CRED_SETRESUID 196 
#define  PRIV_CRED_SETREUID 195 
#define  PRIV_CRED_SETUID 194 
#define  PRIV_DEBUG_DIFFCRED 193 
#define  PRIV_DEBUG_SUGID 192 
#define  PRIV_DEBUG_UNPRIV 191 
#define  PRIV_IPC_ADMIN 190 
#define  PRIV_IPC_MSGSIZE 189 
#define  PRIV_IPC_READ 188 
#define  PRIV_IPC_WRITE 187 
#define  PRIV_JAIL_ATTACH 186 
#define  PRIV_KTRACE 185 
#define  PRIV_MAC_PARTITION 184 
#define  PRIV_MQ_ADMIN 183 
#define  PRIV_MSGBUF 182 
#define  PRIV_NETINET_RAW 181 
#define  PRIV_NETINET_RESERVEDPORT 180 
#define  PRIV_NETINET_REUSEPORT 179 
#define  PRIV_PROC_LIMIT 178 
#define  PRIV_PROC_SETLOGIN 177 
#define  PRIV_PROC_SETRLIMIT 176 
#define  PRIV_SCHED_DIFFCRED 175 
#define  PRIV_SCHED_RTPRIO 174 
#define  PRIV_SCHED_SET 173 
#define  PRIV_SCHED_SETPARAM 172 
#define  PRIV_SCHED_SETPOLICY 171 
#define  PRIV_SCHED_SETPRIORITY 170 
#define  PRIV_SEEOTHERGIDS 169 
#define  PRIV_SEEOTHERUIDS 168 
#define  PRIV_SEM_WRITE 167 
#define  PRIV_SIGNAL_DIFFCRED 166 
#define  PRIV_SIGNAL_SUGID 165 
#define  PRIV_SYSCTL_WRITEJAIL 164 
#define  PRIV_TTY_DRAINWAIT 163 
#define  PRIV_TTY_DTRWAIT 162 
#define  PRIV_TTY_EXCLUSIVE 161 
#define  PRIV_TTY_SETA 160 
#define  PRIV_TTY_STI 159 
#define  PRIV_VFS_ADMIN 158 
#define  PRIV_VFS_CHFLAGS_DEV 157 
#define  PRIV_VFS_CHOWN 156 
#define  PRIV_VFS_CHROOT 155 
#define  PRIV_VFS_EXCEEDQUOTA 154 
#define  PRIV_VFS_EXEC 153 
#define  PRIV_VFS_FCHROOT 152 
#define  PRIV_VFS_FHOPEN 151 
#define  PRIV_VFS_FHSTATFS 150 
#define  PRIV_VFS_GENERATION 149 
#define  PRIV_VFS_GETFH 148 
#define  PRIV_VFS_GETQUOTA 147 
#define  PRIV_VFS_LINK 146 
#define  PRIV_VFS_LOOKUP 145 
#define  PRIV_VFS_MOUNT 144 
#define  PRIV_VFS_MOUNT_NONUSER 143 
#define  PRIV_VFS_MOUNT_OWNER 142 
#define  PRIV_VFS_MOUNT_PERM 141 
#define  PRIV_VFS_MOUNT_SUIDDIR 140 
#define  PRIV_VFS_READ 139 
#define  PRIV_VFS_RETAINSUGID 138 
#define  PRIV_VFS_SETGID 137 
#define  PRIV_VFS_STICKYFILE 136 
#define  PRIV_VFS_SYSFLAGS 135 
#define  PRIV_VFS_UNMOUNT 134 
#define  PRIV_VFS_WRITE 133 
#define  PRIV_VM_MADV_PROTECT 132 
#define  PRIV_VM_MLOCK 131 
#define  PRIV_VM_MUNLOCK 130 
#define  PRIV_VM_SWAP_NOQUOTA 129 
#define  PRIV_VM_SWAP_NORLIMIT 128 
 struct mac_biba* SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  biba_enabled ; 
 int biba_subject_privileged (struct mac_biba*) ; 

__attribute__((used)) static int
biba_priv_check(struct ucred *cred, int priv)
{
	struct mac_biba *subj;
	int error;

	if (!biba_enabled)
		return (0);

	/*
	 * Exempt only specific privileges from the Biba integrity policy.
	 */
	switch (priv) {
	case PRIV_KTRACE:
	case PRIV_MSGBUF:

	/*
	 * Allow processes to manipulate basic process audit properties, and
	 * to submit audit records.
	 */
	case PRIV_AUDIT_GETAUDIT:
	case PRIV_AUDIT_SETAUDIT:
	case PRIV_AUDIT_SUBMIT:

	/*
	 * Allow processes to manipulate their regular UNIX credentials.
	 */
	case PRIV_CRED_SETUID:
	case PRIV_CRED_SETEUID:
	case PRIV_CRED_SETGID:
	case PRIV_CRED_SETEGID:
	case PRIV_CRED_SETGROUPS:
	case PRIV_CRED_SETREUID:
	case PRIV_CRED_SETREGID:
	case PRIV_CRED_SETRESUID:
	case PRIV_CRED_SETRESGID:

	/*
	 * Allow processes to perform system monitoring.
	 */
	case PRIV_SEEOTHERGIDS:
	case PRIV_SEEOTHERUIDS:
		break;

	/*
	 * Allow access to general process debugging facilities.  We
	 * separately control debugging based on MAC label.
	 */
	case PRIV_DEBUG_DIFFCRED:
	case PRIV_DEBUG_SUGID:
	case PRIV_DEBUG_UNPRIV:

	/*
	 * Allow manipulating jails.
	 */
	case PRIV_JAIL_ATTACH:

	/*
	 * Allow privilege with respect to the Partition policy, but not the
	 * Privs policy.
	 */
	case PRIV_MAC_PARTITION:

	/*
	 * Allow privilege with respect to process resource limits and login
	 * context.
	 */
	case PRIV_PROC_LIMIT:
	case PRIV_PROC_SETLOGIN:
	case PRIV_PROC_SETRLIMIT:

	/*
	 * Allow System V and POSIX IPC privileges.
	 */
	case PRIV_IPC_READ:
	case PRIV_IPC_WRITE:
	case PRIV_IPC_ADMIN:
	case PRIV_IPC_MSGSIZE:
	case PRIV_MQ_ADMIN:

	/*
	 * Allow certain scheduler manipulations -- possibly this should be
	 * controlled by more fine-grained policy, as potentially low
	 * integrity processes can deny CPU to higher integrity ones.
	 */
	case PRIV_SCHED_DIFFCRED:
	case PRIV_SCHED_SETPRIORITY:
	case PRIV_SCHED_RTPRIO:
	case PRIV_SCHED_SETPOLICY:
	case PRIV_SCHED_SET:
	case PRIV_SCHED_SETPARAM:

	/*
	 * More IPC privileges.
	 */
	case PRIV_SEM_WRITE:

	/*
	 * Allow signaling privileges subject to integrity policy.
	 */
	case PRIV_SIGNAL_DIFFCRED:
	case PRIV_SIGNAL_SUGID:

	/*
	 * Allow access to only limited sysctls from lower integrity levels;
	 * piggy-back on the Jail definition.
	 */
	case PRIV_SYSCTL_WRITEJAIL:

	/*
	 * Allow TTY-based privileges, subject to general device access using
	 * labels on TTY device nodes, but not console privilege.
	 */
	case PRIV_TTY_DRAINWAIT:
	case PRIV_TTY_DTRWAIT:
	case PRIV_TTY_EXCLUSIVE:
	case PRIV_TTY_STI:
	case PRIV_TTY_SETA:

	/*
	 * Grant most VFS privileges, as almost all are in practice bounded
	 * by more specific checks using labels.
	 */
	case PRIV_VFS_READ:
	case PRIV_VFS_WRITE:
	case PRIV_VFS_ADMIN:
	case PRIV_VFS_EXEC:
	case PRIV_VFS_LOOKUP:
	case PRIV_VFS_CHFLAGS_DEV:
	case PRIV_VFS_CHOWN:
	case PRIV_VFS_CHROOT:
	case PRIV_VFS_RETAINSUGID:
	case PRIV_VFS_EXCEEDQUOTA:
	case PRIV_VFS_FCHROOT:
	case PRIV_VFS_FHOPEN:
	case PRIV_VFS_FHSTATFS:
	case PRIV_VFS_GENERATION:
	case PRIV_VFS_GETFH:
	case PRIV_VFS_GETQUOTA:
	case PRIV_VFS_LINK:
	case PRIV_VFS_MOUNT:
	case PRIV_VFS_MOUNT_OWNER:
	case PRIV_VFS_MOUNT_PERM:
	case PRIV_VFS_MOUNT_SUIDDIR:
	case PRIV_VFS_MOUNT_NONUSER:
	case PRIV_VFS_SETGID:
	case PRIV_VFS_STICKYFILE:
	case PRIV_VFS_SYSFLAGS:
	case PRIV_VFS_UNMOUNT:

	/*
	 * Allow VM privileges; it would be nice if these were subject to
	 * resource limits.
	 */
	case PRIV_VM_MADV_PROTECT:
	case PRIV_VM_MLOCK:
	case PRIV_VM_MUNLOCK:
	case PRIV_VM_SWAP_NOQUOTA:
	case PRIV_VM_SWAP_NORLIMIT:

	/*
	 * Allow some but not all network privileges.  In general, dont allow
	 * reconfiguring the network stack, just normal use.
	 */
	case PRIV_NETINET_RESERVEDPORT:
	case PRIV_NETINET_RAW:
	case PRIV_NETINET_REUSEPORT:
		break;

	/*
	 * All remaining system privileges are allow only if the process
	 * holds privilege with respect to the Biba policy.
	 */
	default:
		subj = SLOT(cred->cr_label);
		error = biba_subject_privileged(subj);
		if (error)
			return (error);
	}
	return (0);
}