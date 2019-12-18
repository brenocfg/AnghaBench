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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  au_event_t ;

/* Variables and functions */
 int ARG_CTLNAME ; 
 int ARG_LEN ; 
 int ARG_VALUE ; 
 int /*<<< orphan*/  AUE_SYSCTL ; 
 int /*<<< orphan*/  AUE_SYSCTL_NONADMIN ; 
#define  KERN_ARGMAX 162 
#define  KERN_BOOTFILE 161 
#define  KERN_BOOTTIME 160 
#define  KERN_CLOCKRATE 159 
#define  KERN_DUMMY 158 
#define  KERN_DUMPDEV 157 
#define  KERN_FILE 156 
#define  KERN_HOSTID 155 
#define  KERN_HOSTNAME 154 
#define  KERN_IOV_MAX 153 
#define  KERN_IPC 152 
#define  KERN_JOB_CONTROL 151 
#define  KERN_LOGSIGEXIT 150 
#define  KERN_MAXFILES 149 
#define  KERN_MAXFILESPERPROC 148 
#define  KERN_MAXPROC 147 
#define  KERN_MAXPROCPERUID 146 
#define  KERN_MAXVNODES 145 
#define  KERN_NGROUPS 144 
#define  KERN_NISDOMAINNAME 143 
#define  KERN_NTP_PLL 142 
#define  KERN_OSRELDATE 141 
#define  KERN_OSRELEASE 140 
#define  KERN_OSREV 139 
#define  KERN_OSTYPE 138 
#define  KERN_POSIX1 137 
#define  KERN_PROC 136 
#define  KERN_PROF 135 
#define  KERN_PS_STRINGS 134 
#define  KERN_SAVED_IDS 133 
#define  KERN_SECURELVL 132 
#define  KERN_UPDATEINTERVAL 131 
#define  KERN_USRSTACK 130 
#define  KERN_VERSION 129 
#define  KERN_VNODE 128 

au_event_t
audit_ctlname_to_sysctlevent(int name[], uint64_t valid_arg)
{

	/* can't parse it - so return the worst case */
	if ((valid_arg & (ARG_CTLNAME | ARG_LEN)) != (ARG_CTLNAME | ARG_LEN))
		return (AUE_SYSCTL);

	switch (name[0]) {
	/* non-admin "lookups" treat them special */
	case KERN_OSTYPE:
	case KERN_OSRELEASE:
	case KERN_OSREV:
	case KERN_VERSION:
	case KERN_ARGMAX:
	case KERN_CLOCKRATE:
	case KERN_BOOTTIME:
	case KERN_POSIX1:
	case KERN_NGROUPS:
	case KERN_JOB_CONTROL:
	case KERN_SAVED_IDS:
	case KERN_OSRELDATE:
	case KERN_DUMMY:
		return (AUE_SYSCTL_NONADMIN);

	/* only treat the changeable controls as admin */
	case KERN_MAXVNODES:
	case KERN_MAXPROC:
	case KERN_MAXFILES:
	case KERN_MAXPROCPERUID:
	case KERN_MAXFILESPERPROC:
	case KERN_HOSTID:
	case KERN_SECURELVL:
	case KERN_HOSTNAME:
	case KERN_VNODE:
	case KERN_PROC:
	case KERN_FILE:
	case KERN_PROF:
	case KERN_NISDOMAINNAME:
	case KERN_UPDATEINTERVAL:
	case KERN_NTP_PLL:
	case KERN_BOOTFILE:
	case KERN_DUMPDEV:
	case KERN_IPC:
	case KERN_PS_STRINGS:
	case KERN_USRSTACK:
	case KERN_LOGSIGEXIT:
	case KERN_IOV_MAX:
		return ((valid_arg & ARG_VALUE) ?
		    AUE_SYSCTL : AUE_SYSCTL_NONADMIN);

	default:
		return (AUE_SYSCTL);
	}
	/* NOTREACHED */
}