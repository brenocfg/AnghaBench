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
struct ucred {TYPE_1__* cr_prison; } ;
struct TYPE_2__ {int pr_flags; int pr_allow; int pr_enforce_statfs; } ;

/* Variables and functions */
 int EPERM ; 
#define  PRIV_AUDIT_GETAUDIT 247 
#define  PRIV_AUDIT_SETAUDIT 246 
#define  PRIV_AUDIT_SUBMIT 245 
#define  PRIV_CRED_SETEGID 244 
#define  PRIV_CRED_SETEUID 243 
#define  PRIV_CRED_SETGID 242 
#define  PRIV_CRED_SETGROUPS 241 
#define  PRIV_CRED_SETREGID 240 
#define  PRIV_CRED_SETRESGID 239 
#define  PRIV_CRED_SETRESUID 238 
#define  PRIV_CRED_SETREUID 237 
#define  PRIV_CRED_SETUID 236 
#define  PRIV_DEBUG_DIFFCRED 235 
#define  PRIV_DEBUG_SUGID 234 
#define  PRIV_DEBUG_UNPRIV 233 
#define  PRIV_IPC_ADMIN 232 
#define  PRIV_IPC_MSGSIZE 231 
#define  PRIV_IPC_READ 230 
#define  PRIV_IPC_WRITE 229 
#define  PRIV_JAIL_ATTACH 228 
#define  PRIV_JAIL_REMOVE 227 
#define  PRIV_JAIL_SET 226 
#define  PRIV_KMEM_READ 225 
#define  PRIV_KTRACE 224 
#define  PRIV_MQ_ADMIN 223 
#define  PRIV_MSGBUF 222 
#define  PRIV_NET80211_GETKEY 221 
#define  PRIV_NET80211_MANAGE 220 
#define  PRIV_NETATM_ADD 219 
#define  PRIV_NETATM_CFG 218 
#define  PRIV_NETATM_DEL 217 
#define  PRIV_NETATM_SET 216 
#define  PRIV_NETBLUETOOTH_RAW 215 
#define  PRIV_NETGRAPH_CONTROL 214 
#define  PRIV_NETGRAPH_TTY 213 
#define  PRIV_NETINET_ADDRCTRL6 212 
#define  PRIV_NETINET_ALIFETIME6 211 
#define  PRIV_NETINET_BINDANY 210 
#define  PRIV_NETINET_CARP 209 
#define  PRIV_NETINET_DIVERT 208 
#define  PRIV_NETINET_DUMMYNET 207 
#define  PRIV_NETINET_GETCRED 206 
#define  PRIV_NETINET_IPFW 205 
#define  PRIV_NETINET_IPSEC 204 
#define  PRIV_NETINET_MROUTE 203 
#define  PRIV_NETINET_ND6 202 
#define  PRIV_NETINET_PF 201 
#define  PRIV_NETINET_RAW 200 
#define  PRIV_NETINET_RESERVEDPORT 199 
#define  PRIV_NETINET_REUSEPORT 198 
#define  PRIV_NETINET_SCOPE6 197 
#define  PRIV_NETINET_SETHDROPTS 196 
#define  PRIV_NETNCP 195 
#define  PRIV_NETSMB 194 
#define  PRIV_NET_ADDIFADDR 193 
#define  PRIV_NET_ADDIFGROUP 192 
#define  PRIV_NET_ADDMULTI 191 
#define  PRIV_NET_BPF 190 
#define  PRIV_NET_BRIDGE 189 
#define  PRIV_NET_DELIFADDR 188 
#define  PRIV_NET_DELIFGROUP 187 
#define  PRIV_NET_DELMULTI 186 
#define  PRIV_NET_GIF 185 
#define  PRIV_NET_GRE 184 
#define  PRIV_NET_HWIOCTL 183 
#define  PRIV_NET_IFCREATE 182 
#define  PRIV_NET_IFDESTROY 181 
#define  PRIV_NET_LAGG 180 
#define  PRIV_NET_RAW 179 
#define  PRIV_NET_ROUTE 178 
#define  PRIV_NET_SETIFCAP 177 
#define  PRIV_NET_SETIFDESCR 176 
#define  PRIV_NET_SETIFFIB 175 
#define  PRIV_NET_SETIFFLAGS 174 
#define  PRIV_NET_SETIFMAC 173 
#define  PRIV_NET_SETIFMETRIC 172 
#define  PRIV_NET_SETIFMTU 171 
#define  PRIV_NET_SETIFNAME 170 
#define  PRIV_NET_SETIFPHYS 169 
#define  PRIV_NET_SETIFVNET 168 
#define  PRIV_NET_SETLANPCP 167 
#define  PRIV_NET_SETLLADDR 166 
#define  PRIV_NET_TAP 165 
#define  PRIV_NFS_DAEMON 164 
#define  PRIV_NFS_LOCKD 163 
#define  PRIV_PROC_LIMIT 162 
#define  PRIV_PROC_SETLOGIN 161 
#define  PRIV_PROC_SETLOGINCLASS 160 
#define  PRIV_PROC_SETRLIMIT 159 
#define  PRIV_SCHED_CPUSET 158 
#define  PRIV_SCHED_DIFFCRED 157 
#define  PRIV_SEEOTHERGIDS 156 
#define  PRIV_SEEOTHERUIDS 155 
#define  PRIV_SIGNAL_DIFFCRED 154 
#define  PRIV_SIGNAL_SUGID 153 
#define  PRIV_SYSCTL_WRITEJAIL 152 
#define  PRIV_VFS_ADMIN 151 
#define  PRIV_VFS_BLOCKRESERVE 150 
#define  PRIV_VFS_CHFLAGS_DEV 149 
#define  PRIV_VFS_CHOWN 148 
#define  PRIV_VFS_CHROOT 147 
#define  PRIV_VFS_EXEC 146 
#define  PRIV_VFS_FCHROOT 145 
#define  PRIV_VFS_GETQUOTA 144 
#define  PRIV_VFS_LINK 143 
#define  PRIV_VFS_LOOKUP 142 
#define  PRIV_VFS_MOUNT 141 
#define  PRIV_VFS_MOUNT_NONUSER 140 
#define  PRIV_VFS_MOUNT_OWNER 139 
#define  PRIV_VFS_READ 138 
#define  PRIV_VFS_RETAINSUGID 137 
#define  PRIV_VFS_SETGID 136 
#define  PRIV_VFS_SETQUOTA 135 
#define  PRIV_VFS_STAT 134 
#define  PRIV_VFS_STICKYFILE 133 
#define  PRIV_VFS_SYSFLAGS 132 
#define  PRIV_VFS_UNMOUNT 131 
#define  PRIV_VFS_WRITE 130 
#define  PRIV_VM_MLOCK 129 
#define  PRIV_VM_MUNLOCK 128 
 int PR_ALLOW_CHFLAGS ; 
 int PR_ALLOW_MLOCK ; 
 int PR_ALLOW_MOUNT ; 
 int PR_ALLOW_RAW_SOCKETS ; 
 int PR_ALLOW_READ_MSGBUF ; 
 int PR_ALLOW_RESERVED_PORTS ; 
 int PR_VNET ; 
 int /*<<< orphan*/  jailed (struct ucred*) ; 

int
prison_priv_check(struct ucred *cred, int priv)
{

	if (!jailed(cred))
		return (0);

#ifdef VIMAGE
	/*
	 * Privileges specific to prisons with a virtual network stack.
	 * There might be a duplicate entry here in case the privilege
	 * is only granted conditionally in the legacy jail case.
	 */
	switch (priv) {
#ifdef notyet
		/*
		 * NFS-specific privileges.
		 */
	case PRIV_NFS_DAEMON:
	case PRIV_NFS_LOCKD:
#endif
		/*
		 * Network stack privileges.
		 */
	case PRIV_NET_BRIDGE:
	case PRIV_NET_GRE:
	case PRIV_NET_BPF:
	case PRIV_NET_RAW:		/* Dup, cond. in legacy jail case. */
	case PRIV_NET_ROUTE:
	case PRIV_NET_TAP:
	case PRIV_NET_SETIFMTU:
	case PRIV_NET_SETIFFLAGS:
	case PRIV_NET_SETIFCAP:
	case PRIV_NET_SETIFDESCR:
	case PRIV_NET_SETIFNAME	:
	case PRIV_NET_SETIFMETRIC:
	case PRIV_NET_SETIFPHYS:
	case PRIV_NET_SETIFMAC:
	case PRIV_NET_SETLANPCP:
	case PRIV_NET_ADDMULTI:
	case PRIV_NET_DELMULTI:
	case PRIV_NET_HWIOCTL:
	case PRIV_NET_SETLLADDR:
	case PRIV_NET_ADDIFGROUP:
	case PRIV_NET_DELIFGROUP:
	case PRIV_NET_IFCREATE:
	case PRIV_NET_IFDESTROY:
	case PRIV_NET_ADDIFADDR:
	case PRIV_NET_DELIFADDR:
	case PRIV_NET_LAGG:
	case PRIV_NET_GIF:
	case PRIV_NET_SETIFVNET:
	case PRIV_NET_SETIFFIB:

		/*
		 * 802.11-related privileges.
		 */
	case PRIV_NET80211_GETKEY:
#ifdef notyet
	case PRIV_NET80211_MANAGE:		/* XXX-BZ discuss with sam@ */
#endif

#ifdef notyet
		/*
		 * ATM privileges.
		 */
	case PRIV_NETATM_CFG:
	case PRIV_NETATM_ADD:
	case PRIV_NETATM_DEL:
	case PRIV_NETATM_SET:

		/*
		 * Bluetooth privileges.
		 */
	case PRIV_NETBLUETOOTH_RAW:
#endif

		/*
		 * Netgraph and netgraph module privileges.
		 */
	case PRIV_NETGRAPH_CONTROL:
#ifdef notyet
	case PRIV_NETGRAPH_TTY:
#endif

		/*
		 * IPv4 and IPv6 privileges.
		 */
	case PRIV_NETINET_IPFW:
	case PRIV_NETINET_DIVERT:
	case PRIV_NETINET_PF:
	case PRIV_NETINET_DUMMYNET:
	case PRIV_NETINET_CARP:
	case PRIV_NETINET_MROUTE:
	case PRIV_NETINET_RAW:
	case PRIV_NETINET_ADDRCTRL6:
	case PRIV_NETINET_ND6:
	case PRIV_NETINET_SCOPE6:
	case PRIV_NETINET_ALIFETIME6:
	case PRIV_NETINET_IPSEC:
	case PRIV_NETINET_BINDANY:

#ifdef notyet
		/*
		 * NCP privileges.
		 */
	case PRIV_NETNCP:

		/*
		 * SMB privileges.
		 */
	case PRIV_NETSMB:
#endif

	/*
	 * No default: or deny here.
	 * In case of no permit fall through to next switch().
	 */
		if (cred->cr_prison->pr_flags & PR_VNET)
			return (0);
	}
#endif /* VIMAGE */

	switch (priv) {

		/*
		 * Allow ktrace privileges for root in jail.
		 */
	case PRIV_KTRACE:

#if 0
		/*
		 * Allow jailed processes to configure audit identity and
		 * submit audit records (login, etc).  In the future we may
		 * want to further refine the relationship between audit and
		 * jail.
		 */
	case PRIV_AUDIT_GETAUDIT:
	case PRIV_AUDIT_SETAUDIT:
	case PRIV_AUDIT_SUBMIT:
#endif

		/*
		 * Allow jailed processes to manipulate process UNIX
		 * credentials in any way they see fit.
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
		 * Jail implements visibility constraints already, so allow
		 * jailed root to override uid/gid-based constraints.
		 */
	case PRIV_SEEOTHERGIDS:
	case PRIV_SEEOTHERUIDS:

		/*
		 * Jail implements inter-process debugging limits already, so
		 * allow jailed root various debugging privileges.
		 */
	case PRIV_DEBUG_DIFFCRED:
	case PRIV_DEBUG_SUGID:
	case PRIV_DEBUG_UNPRIV:

		/*
		 * Allow jail to set various resource limits and login
		 * properties, and for now, exceed process resource limits.
		 */
	case PRIV_PROC_LIMIT:
	case PRIV_PROC_SETLOGIN:
	case PRIV_PROC_SETRLIMIT:

		/*
		 * System V and POSIX IPC privileges are granted in jail.
		 */
	case PRIV_IPC_READ:
	case PRIV_IPC_WRITE:
	case PRIV_IPC_ADMIN:
	case PRIV_IPC_MSGSIZE:
	case PRIV_MQ_ADMIN:

		/*
		 * Jail operations within a jail work on child jails.
		 */
	case PRIV_JAIL_ATTACH:
	case PRIV_JAIL_SET:
	case PRIV_JAIL_REMOVE:

		/*
		 * Jail implements its own inter-process limits, so allow
		 * root processes in jail to change scheduling on other
		 * processes in the same jail.  Likewise for signalling.
		 */
	case PRIV_SCHED_DIFFCRED:
	case PRIV_SCHED_CPUSET:
	case PRIV_SIGNAL_DIFFCRED:
	case PRIV_SIGNAL_SUGID:

		/*
		 * Allow jailed processes to write to sysctls marked as jail
		 * writable.
		 */
	case PRIV_SYSCTL_WRITEJAIL:

		/*
		 * Allow root in jail to manage a variety of quota
		 * properties.  These should likely be conditional on a
		 * configuration option.
		 */
	case PRIV_VFS_GETQUOTA:
	case PRIV_VFS_SETQUOTA:

		/*
		 * Since Jail relies on chroot() to implement file system
		 * protections, grant many VFS privileges to root in jail.
		 * Be careful to exclude mount-related and NFS-related
		 * privileges.
		 */
	case PRIV_VFS_READ:
	case PRIV_VFS_WRITE:
	case PRIV_VFS_ADMIN:
	case PRIV_VFS_EXEC:
	case PRIV_VFS_LOOKUP:
	case PRIV_VFS_BLOCKRESERVE:	/* XXXRW: Slightly surprising. */
	case PRIV_VFS_CHFLAGS_DEV:
	case PRIV_VFS_CHOWN:
	case PRIV_VFS_CHROOT:
	case PRIV_VFS_RETAINSUGID:
	case PRIV_VFS_FCHROOT:
	case PRIV_VFS_LINK:
	case PRIV_VFS_SETGID:
	case PRIV_VFS_STAT:
	case PRIV_VFS_STICKYFILE:

		/*
		 * As in the non-jail case, non-root users are expected to be
		 * able to read kernel/phyiscal memory (provided /dev/[k]mem
		 * exists in the jail and they have permission to access it).
		 */
	case PRIV_KMEM_READ:
		return (0);

		/*
		 * Depending on the global setting, allow privilege of
		 * setting system flags.
		 */
	case PRIV_VFS_SYSFLAGS:
		if (cred->cr_prison->pr_allow & PR_ALLOW_CHFLAGS)
			return (0);
		else
			return (EPERM);

		/*
		 * Depending on the global setting, allow privilege of
		 * mounting/unmounting file systems.
		 */
	case PRIV_VFS_MOUNT:
	case PRIV_VFS_UNMOUNT:
	case PRIV_VFS_MOUNT_NONUSER:
	case PRIV_VFS_MOUNT_OWNER:
		if (cred->cr_prison->pr_allow & PR_ALLOW_MOUNT &&
		    cred->cr_prison->pr_enforce_statfs < 2)
			return (0);
		else
			return (EPERM);

		/*
		 * Conditionnaly allow locking (unlocking) physical pages
		 * in memory.
		 */
	case PRIV_VM_MLOCK:
	case PRIV_VM_MUNLOCK:
		if (cred->cr_prison->pr_allow & PR_ALLOW_MLOCK)
			return (0);
		else
			return (EPERM);

		/*
		 * Conditionally allow jailed root to bind reserved ports.
		 */
	case PRIV_NETINET_RESERVEDPORT:
		if (cred->cr_prison->pr_allow & PR_ALLOW_RESERVED_PORTS)
			return (0);
		else
			return (EPERM);

		/*
		 * Allow jailed root to reuse in-use ports.
		 */
	case PRIV_NETINET_REUSEPORT:
		return (0);

		/*
		 * Allow jailed root to set certain IPv4/6 (option) headers.
		 */
	case PRIV_NETINET_SETHDROPTS:
		return (0);

		/*
		 * Conditionally allow creating raw sockets in jail.
		 */
	case PRIV_NETINET_RAW:
		if (cred->cr_prison->pr_allow & PR_ALLOW_RAW_SOCKETS)
			return (0);
		else
			return (EPERM);

		/*
		 * Since jail implements its own visibility limits on netstat
		 * sysctls, allow getcred.  This allows identd to work in
		 * jail.
		 */
	case PRIV_NETINET_GETCRED:
		return (0);

		/*
		 * Allow jailed root to set loginclass.
		 */
	case PRIV_PROC_SETLOGINCLASS:
		return (0);

		/*
		 * Do not allow a process inside a jail to read the kernel
		 * message buffer unless explicitly permitted.
		 */
	case PRIV_MSGBUF:
		if (cred->cr_prison->pr_allow & PR_ALLOW_READ_MSGBUF)
			return (0);
		return (EPERM);

	default:
		/*
		 * In all remaining cases, deny the privilege request.  This
		 * includes almost all network privileges, many system
		 * configuration privileges.
		 */
		return (EPERM);
	}
}