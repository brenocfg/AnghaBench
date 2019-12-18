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
typedef  int exm_t ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
#define  EXM_EMPTYBUF 138 
#define  EXM_FILECOUNT 137 
#define  EXM_NOCANON 136 
#define  EXM_NOCANON_F 135 
#define  EXM_NOFILEYET 134 
#define  EXM_NOPREVBUF 133 
#define  EXM_NOPREVRE 132 
#define  EXM_NOSUSPEND 131 
#define  EXM_SECURE 130 
#define  EXM_SECURE_F 129 
#define  EXM_USAGE 128 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msgq_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 

void
ex_emsg(SCR *sp, char *p, exm_t which)
{
	switch (which) {
	case EXM_EMPTYBUF:
		msgq(sp, M_ERR, "168|Buffer %s is empty", p);
		break;
	case EXM_FILECOUNT:
		 msgq_str(sp, M_ERR, p, 
		     "144|%s: expanded into too many file names");
		break;
	case EXM_NOCANON:
		msgq(sp, M_ERR,
		    "283|The %s command requires the ex terminal interface", p);
		break;
	case EXM_NOCANON_F:
		msgq(sp, M_ERR,
		    "272|That form of %s requires the ex terminal interface",
		    p);
		break;
	case EXM_NOFILEYET:
		if (p == NULL)
			msgq(sp, M_ERR,
			    "274|Command failed, no file read in yet.");
		else
			msgq(sp, M_ERR,
	"173|The %s command requires that a file have already been read in", p);
		break;
	case EXM_NOPREVBUF:
		msgq(sp, M_ERR, "171|No previous buffer to execute");
		break;
	case EXM_NOPREVRE:
		msgq(sp, M_ERR, "172|No previous regular expression");
		break;
	case EXM_NOSUSPEND:
		msgq(sp, M_ERR, "230|This screen may not be suspended");
		break;
	case EXM_SECURE:
		msgq(sp, M_ERR,
"290|The %s command is not supported when the secure edit option is set", p);
		break;
	case EXM_SECURE_F:
		msgq(sp, M_ERR,
"284|That form of %s is not supported when the secure edit option is set", p);
		break;
	case EXM_USAGE:
		msgq(sp, M_ERR, "174|Usage: %s", p);
		break;
	}
}