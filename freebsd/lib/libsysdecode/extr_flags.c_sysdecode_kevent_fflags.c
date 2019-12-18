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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  EVFILT_PROC 134 
#define  EVFILT_PROCDESC 133 
#define  EVFILT_READ 132 
#define  EVFILT_TIMER 131 
#define  EVFILT_USER 130 
#define  EVFILT_VNODE 129 
#define  EVFILT_WRITE 128 
 int NOTE_FFCTRLMASK ; 
 int NOTE_FFLAGSMASK ; 
 unsigned int NOTE_FFNOP ; 
 int NOTE_TRIGGER ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kevent_proc_fflags ; 
 int /*<<< orphan*/  kevent_rdwr_fflags ; 
 int /*<<< orphan*/  kevent_timer_fflags ; 
 int /*<<< orphan*/  kevent_user_ffctrl ; 
 int /*<<< orphan*/  kevent_vnode_fflags ; 
 char* lookup_value (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  print_integer (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  print_mask_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 

void
sysdecode_kevent_fflags(FILE *fp, short filter, int fflags, int base)
{
	int rem;

	if (fflags == 0) {
		fputs("0", fp);
		return;
	}

	switch (filter) {
	case EVFILT_READ:
	case EVFILT_WRITE:
		if (!print_mask_int(fp, kevent_rdwr_fflags, fflags, &rem))
			fprintf(fp, "%#x", rem);
		else if (rem != 0)
			fprintf(fp, "|%#x", rem);
		break;
	case EVFILT_VNODE:
		if (!print_mask_int(fp, kevent_vnode_fflags, fflags, &rem))
			fprintf(fp, "%#x", rem);
		else if (rem != 0)
			fprintf(fp, "|%#x", rem);
		break;
	case EVFILT_PROC:
	case EVFILT_PROCDESC:
		if (!print_mask_int(fp, kevent_proc_fflags, fflags, &rem))
			fprintf(fp, "%#x", rem);
		else if (rem != 0)
			fprintf(fp, "|%#x", rem);
		break;
	case EVFILT_TIMER:
		if (!print_mask_int(fp, kevent_timer_fflags, fflags, &rem))
			fprintf(fp, "%#x", rem);
		else if (rem != 0)
			fprintf(fp, "|%#x", rem);
		break;
	case EVFILT_USER: {
		unsigned int ctrl, data;

		ctrl = fflags & NOTE_FFCTRLMASK;
		data = fflags & NOTE_FFLAGSMASK;

		if (fflags & NOTE_TRIGGER) {
			fputs("NOTE_TRIGGER", fp);
			if (fflags == NOTE_TRIGGER)
				return;
			fputc('|', fp);
		}

		/*
		 * An event with 'ctrl' == NOTE_FFNOP is either a reported
		 * (output) event for which only 'data' should be output
		 * or a pointless input event.  Assume that pointless
		 * input events don't occur in practice.  An event with
		 * NOTE_TRIGGER is always an input event.
		 */
		if (ctrl != NOTE_FFNOP || fflags & NOTE_TRIGGER) {
			fprintf(fp, "%s|%#x",
			    lookup_value(kevent_user_ffctrl, ctrl), data);
		} else {
			print_integer(fp, data, base);
		}
		break;
	}
	default:
		print_integer(fp, fflags, base);
		break;
	}
}