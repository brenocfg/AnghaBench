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
#define  KF_FD_TYPE_CTTY 133 
#define  KF_FD_TYPE_CWD 132 
#define  KF_FD_TYPE_JAIL 131 
#define  KF_FD_TYPE_ROOT 130 
#define  KF_FD_TYPE_TEXT 129 
#define  KF_FD_TYPE_TRACE 128 
 int PS_FST_UFLAG_CDIR ; 
 int PS_FST_UFLAG_CTTY ; 
 int PS_FST_UFLAG_JAIL ; 
 int PS_FST_UFLAG_RDIR ; 
 int PS_FST_UFLAG_TEXT ; 
 int PS_FST_UFLAG_TRACE ; 

__attribute__((used)) static int
kinfo_uflags2fst(int fd)
{

	switch (fd) {
	case KF_FD_TYPE_CTTY:
		return (PS_FST_UFLAG_CTTY);
	case KF_FD_TYPE_CWD:
		return (PS_FST_UFLAG_CDIR);
	case KF_FD_TYPE_JAIL:
		return (PS_FST_UFLAG_JAIL);
	case KF_FD_TYPE_TEXT:
		return (PS_FST_UFLAG_TEXT);
	case KF_FD_TYPE_TRACE:
		return (PS_FST_UFLAG_TRACE);
	case KF_FD_TYPE_ROOT:
		return (PS_FST_UFLAG_RDIR);
	}
	return (0);
}