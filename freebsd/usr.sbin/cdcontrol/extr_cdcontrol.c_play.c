#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ioc_toc_header {int ending_track; int starting_track; } ;
struct cd_toc_entry {int dummy; } ;
struct TYPE_4__ {unsigned char minute; unsigned char second; unsigned char frame; } ;
struct TYPE_5__ {int /*<<< orphan*/  lba; TYPE_1__ msf; } ;
struct TYPE_6__ {TYPE_2__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDIOREADTOCHEADER ; 
 int /*<<< orphan*/  fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ioc_toc_header*) ; 
 int /*<<< orphan*/  lba2msf (int,unsigned char*,unsigned char*,unsigned char*) ; 
 scalar_t__ msf ; 
 int msf2lba (unsigned char,unsigned char,unsigned char) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int play_blocks (int,int) ; 
 int play_msf (unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int play_track (int,int,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_toc_entrys (unsigned int) ; 
 int sscanf (char*,char*,...) ; 
 scalar_t__ strchr (char*,char) ; 
 TYPE_3__* toc_buffer ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
play(char *arg)
{
	struct ioc_toc_header h;
	unsigned int n;
	int rc, start, end = 0, istart = 1, iend = 1;

	rc = ioctl (fd, CDIOREADTOCHEADER, &h);

	if (rc < 0)
		return (rc);

	n = h.ending_track - h.starting_track + 1;
	rc = read_toc_entrys ((n + 1) * sizeof (struct cd_toc_entry));

	if (rc < 0)
		return (rc);

	if (! arg || ! *arg) {
		/* Play the whole disc */
		if (msf)
			return play_blocks (0, msf2lba (toc_buffer[n].addr.msf.minute,
							toc_buffer[n].addr.msf.second,
							toc_buffer[n].addr.msf.frame));
		else
			return play_blocks (0, ntohl(toc_buffer[n].addr.lba));
	}

	if (strchr (arg, '#')) {
		/* Play block #blk [ len ] */
		int blk, len = 0;

		if (2 != sscanf (arg, "#%d%d", &blk, &len) &&
		    1 != sscanf (arg, "#%d", &blk))
			goto Clean_up;

		if (len == 0) {
			if (msf)
				len = msf2lba (toc_buffer[n].addr.msf.minute,
					       toc_buffer[n].addr.msf.second,
					       toc_buffer[n].addr.msf.frame) - blk;
			else
				len = ntohl(toc_buffer[n].addr.lba) - blk;
		}
		return play_blocks (blk, len);
	}

	if (strchr (arg, ':')) {
		/*
		 * Play MSF m1:s1 [ .f1 ] [ m2:s2 [ .f2 ] ]
		 *
		 * Will now also undestand timed addresses relative
		 * to the beginning of a track in the form...
		 *
		 *      tr1 m1:s1[.f1] [[tr2] [m2:s2[.f2]]]
		 */
		unsigned tr1, tr2;
		unsigned m1, m2, s1, s2, f1, f2;
		unsigned char tm, ts, tf;

		tr2 = m2 = s2 = f2 = f1 = 0;
		if (8 == sscanf (arg, "%d %d:%d.%d %d %d:%d.%d",
		    &tr1, &m1, &s1, &f1, &tr2, &m2, &s2, &f2))
			goto Play_Relative_Addresses;

		tr2 = m2 = s2 = f2 = f1 = 0;
		if (7 == sscanf (arg, "%d %d:%d %d %d:%d.%d",
		    &tr1, &m1, &s1, &tr2, &m2, &s2, &f2))
			goto Play_Relative_Addresses;

		tr2 = m2 = s2 = f2 = f1 = 0;
		if (7 == sscanf (arg, "%d %d:%d.%d %d %d:%d",
		    &tr1, &m1, &s1, &f1, &tr2, &m2, &s2))
			goto Play_Relative_Addresses;

		tr2 = m2 = s2 = f2 = f1 = 0;
		if (7 == sscanf (arg, "%d %d:%d.%d %d:%d.%d",
		    &tr1, &m1, &s1, &f1, &m2, &s2, &f2))
			goto Play_Relative_Addresses;

		tr2 = m2 = s2 = f2 = f1 = 0;
		if (6 == sscanf (arg, "%d %d:%d.%d %d:%d",
		    &tr1, &m1, &s1, &f1, &m2, &s2))
			goto Play_Relative_Addresses;

		tr2 = m2 = s2 = f2 = f1 = 0;
		if (6 == sscanf (arg, "%d %d:%d %d:%d.%d",
		    &tr1, &m1, &s1, &m2, &s2, &f2))
			goto Play_Relative_Addresses;

		tr2 = m2 = s2 = f2 = f1 = 0;
		if (6 == sscanf (arg, "%d %d:%d.%d %d %d",
		    &tr1, &m1, &s1, &f1, &tr2, &m2))
			goto Play_Relative_Addresses;

		tr2 = m2 = s2 = f2 = f1 = 0;
		if (5 == sscanf (arg, "%d %d:%d %d:%d", &tr1, &m1, &s1, &m2, &s2))
			goto Play_Relative_Addresses;

		tr2 = m2 = s2 = f2 = f1 = 0;
		if (5 == sscanf (arg, "%d %d:%d %d %d",
		    &tr1, &m1, &s1, &tr2, &m2))
			goto Play_Relative_Addresses;

		tr2 = m2 = s2 = f2 = f1 = 0;
		if (5 == sscanf (arg, "%d %d:%d.%d %d",
		    &tr1, &m1, &s1, &f1, &tr2))
			goto Play_Relative_Addresses;

		tr2 = m2 = s2 = f2 = f1 = 0;
		if (4 == sscanf (arg, "%d %d:%d %d", &tr1, &m1, &s1, &tr2))
			goto Play_Relative_Addresses;

		tr2 = m2 = s2 = f2 = f1 = 0;
		if (4 == sscanf (arg, "%d %d:%d.%d", &tr1, &m1, &s1, &f1))
			goto Play_Relative_Addresses;

		tr2 = m2 = s2 = f2 = f1 = 0;
		if (3 == sscanf (arg, "%d %d:%d", &tr1, &m1, &s1))
			goto Play_Relative_Addresses;

		tr2 = m2 = s2 = f2 = f1 = 0;
		goto Try_Absolute_Timed_Addresses;

Play_Relative_Addresses:
		if (! tr1)
			tr1 = 1;
		else if (tr1 > n)
			tr1 = n;

		tr1--;

		if (msf) {
			tm = toc_buffer[tr1].addr.msf.minute;
			ts = toc_buffer[tr1].addr.msf.second;
			tf = toc_buffer[tr1].addr.msf.frame;
		} else
			lba2msf(ntohl(toc_buffer[tr1].addr.lba),
				&tm, &ts, &tf);
		if ((m1 > tm)
		    || ((m1 == tm)
		    && ((s1 > ts)
		    || ((s1 == ts)
		    && (f1 > tf))))) {
			printf ("Track %d is not that long.\n", tr1);
			return (0);
		}

		f1 += tf;
		if (f1 >= 75) {
			s1 += f1 / 75;
			f1 %= 75;
		}

		s1 += ts;
		if (s1 >= 60) {
			m1 += s1 / 60;
			s1 %= 60;
		}

		m1 += tm;

		if (! tr2) {
			if (m2 || s2 || f2) {
				tr2 = tr1;
				f2 += f1;
				if (f2 >= 75) {
					s2 += f2 / 75;
					f2 %= 75;
				}

				s2 += s1;
				if (s2 > 60) {
					m2 += s2 / 60;
					s2 %= 60;
				}

				m2 += m1;
			} else {
				tr2 = n;
				if (msf) {
					m2 = toc_buffer[n].addr.msf.minute;
					s2 = toc_buffer[n].addr.msf.second;
					f2 = toc_buffer[n].addr.msf.frame;
				} else {
					lba2msf(ntohl(toc_buffer[n].addr.lba),
						&tm, &ts, &tf);
					m2 = tm;
					s2 = ts;
					f2 = tf;
				}
			}
		} else if (tr2 > n) {
			tr2 = n;
			m2 = s2 = f2 = 0;
		} else {
			if (m2 || s2 || f2)
				tr2--;
			if (msf) {
				tm = toc_buffer[tr2].addr.msf.minute;
				ts = toc_buffer[tr2].addr.msf.second;
				tf = toc_buffer[tr2].addr.msf.frame;
			} else
				lba2msf(ntohl(toc_buffer[tr2].addr.lba),
					&tm, &ts, &tf);
			f2 += tf;
			if (f2 >= 75) {
				s2 += f2 / 75;
				f2 %= 75;
			}

			s2 += ts;
			if (s2 > 60) {
				m2 += s2 / 60;
				s2 %= 60;
			}

			m2 += tm;
		}

		if (msf) {
			tm = toc_buffer[n].addr.msf.minute;
			ts = toc_buffer[n].addr.msf.second;
			tf = toc_buffer[n].addr.msf.frame;
		} else
			lba2msf(ntohl(toc_buffer[n].addr.lba),
				&tm, &ts, &tf);
		if ((tr2 < n)
		    && ((m2 > tm)
		    || ((m2 == tm)
		    && ((s2 > ts)
		    || ((s2 == ts)
		    && (f2 > tf)))))) {
			printf ("The playing time of the disc is not that long.\n");
			return (0);
		}
		return (play_msf (m1, s1, f1, m2, s2, f2));

Try_Absolute_Timed_Addresses:
		if (6 != sscanf (arg, "%d:%d.%d%d:%d.%d",
			&m1, &s1, &f1, &m2, &s2, &f2) &&
		    5 != sscanf (arg, "%d:%d.%d%d:%d", &m1, &s1, &f1, &m2, &s2) &&
		    5 != sscanf (arg, "%d:%d%d:%d.%d", &m1, &s1, &m2, &s2, &f2) &&
		    3 != sscanf (arg, "%d:%d.%d", &m1, &s1, &f1) &&
		    4 != sscanf (arg, "%d:%d%d:%d", &m1, &s1, &m2, &s2) &&
		    2 != sscanf (arg, "%d:%d", &m1, &s1))
			goto Clean_up;

		if (m2 == 0) {
			if (msf) {
				m2 = toc_buffer[n].addr.msf.minute;
				s2 = toc_buffer[n].addr.msf.second;
				f2 = toc_buffer[n].addr.msf.frame;
			} else {
				lba2msf(ntohl(toc_buffer[n].addr.lba),
					&tm, &ts, &tf);
				m2 = tm;
				s2 = ts;
				f2 = tf;
			}
		}
		return play_msf (m1, s1, f1, m2, s2, f2);
	}

	/*
	 * Play track trk1 [ .idx1 ] [ trk2 [ .idx2 ] ]
	 */
	if (4 != sscanf (arg, "%d.%d%d.%d", &start, &istart, &end, &iend) &&
	    3 != sscanf (arg, "%d.%d%d", &start, &istart, &end) &&
	    3 != sscanf (arg, "%d%d.%d", &start, &end, &iend) &&
	    2 != sscanf (arg, "%d.%d", &start, &istart) &&
	    2 != sscanf (arg, "%d%d", &start, &end) &&
	    1 != sscanf (arg, "%d", &start))
		goto Clean_up;

	if (end == 0)
		end = n;
	return (play_track (start, istart, end, iend));

Clean_up:
	warnx("invalid command arguments");
	return (0);
}