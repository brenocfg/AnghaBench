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
typedef  int /*<<< orphan*/  u_int ;
struct msgbuf {int msg_lastpri; int msg_flags; int /*<<< orphan*/  msg_lock; int /*<<< orphan*/  msg_wseq; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MAXPRIBUF ; 
 int MSGBUF_NEEDNL ; 
 int /*<<< orphan*/  msgbuf_do_addchar (struct msgbuf*,int /*<<< orphan*/ *,char const) ; 
 scalar_t__ msgbuf_show_timestamp ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 size_t sprintf (char*,char*,int) ; 
 size_t strlen (char const*) ; 
 scalar_t__ time_uptime ; 

void
msgbuf_addstr(struct msgbuf *mbp, int pri, const char *str, int filter_cr)
{
	u_int seq;
	size_t len, prefix_len;
	char prefix[MAXPRIBUF];
	char buf[32];
	int i, j, needtime;

	len = strlen(str);
	prefix_len = 0;

	/* If we have a zero-length string, no need to do anything. */
	if (len == 0)
		return;

	mtx_lock_spin(&mbp->msg_lock);

	/*
	 * If this is true, we may need to insert a new priority sequence,
	 * so prepare the prefix.
	 */
	if (pri != -1)
		prefix_len = sprintf(prefix, "<%d>", pri);

	/*
	 * Starting write sequence number.
	 */
	seq = mbp->msg_wseq;

	/*
	 * Whenever there is a change in priority, we have to insert a
	 * newline, and a priority prefix if the priority is not -1.  Here
	 * we detect whether there was a priority change, and whether we
	 * did not end with a newline.  If that is the case, we need to
	 * insert a newline before this string.
	 */
	if (mbp->msg_lastpri != pri && (mbp->msg_flags & MSGBUF_NEEDNL) != 0) {

		msgbuf_do_addchar(mbp, &seq, '\n');
		mbp->msg_flags &= ~MSGBUF_NEEDNL;
	}

	needtime = 1;
	for (i = 0; i < len; i++) {
		/*
		 * If we just had a newline, and the priority is not -1
		 * (and therefore prefix_len != 0), then we need a priority
		 * prefix for this line.
		 */
		if ((mbp->msg_flags & MSGBUF_NEEDNL) == 0 && prefix_len != 0) {
			int j;

			for (j = 0; j < prefix_len; j++)
				msgbuf_do_addchar(mbp, &seq, prefix[j]);
		}

		if (msgbuf_show_timestamp && needtime == 1 &&
		    (mbp->msg_flags & MSGBUF_NEEDNL) == 0) {

			snprintf(buf, sizeof(buf), "[%jd] ",
			    (intmax_t)time_uptime);
			for (j = 0; buf[j] != '\0'; j++)
				msgbuf_do_addchar(mbp, &seq, buf[j]);
			needtime = 0;
		}

		/*
		 * Don't copy carriage returns if the caller requested
		 * filtering.
		 * 
		 * XXX This matches the behavior of msglogchar(), but is it
		 * necessary?  Testing has shown that we don't seem to get
		 * carriage returns here.
		 */
		if ((filter_cr != 0) && (str[i] == '\r'))
			continue;

		/*
		 * Clear this flag if we see a newline.  This affects whether
		 * we need to insert a new prefix or insert a newline later.
		 */
		if (str[i] == '\n')
			mbp->msg_flags &= ~MSGBUF_NEEDNL;
		else
			mbp->msg_flags |= MSGBUF_NEEDNL;

		msgbuf_do_addchar(mbp, &seq, str[i]);
	}
	/*
	 * Update the write sequence number for the actual number of
	 * characters we put in the message buffer.  (Depends on whether
	 * carriage returns are filtered.)
	 */
	mbp->msg_wseq = seq;

	/*
	 * Set the last priority.
	 */
	mbp->msg_lastpri = pri;

	mtx_unlock_spin(&mbp->msg_lock);

}