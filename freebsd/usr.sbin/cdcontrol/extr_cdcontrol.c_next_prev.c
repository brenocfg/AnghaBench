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
struct ioc_toc_header {int ending_track; int starting_track; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDIOREADTOCHEADER ; 
 int CMD_NEXT ; 
 int /*<<< orphan*/  fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ioc_toc_header*) ; 
 int play_track (int,int,int,int) ; 
 int sscanf (char*,char*,int*) ; 
 int status (int*,int*,int*,int*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
next_prev(char *arg, int cmd)
{
	struct ioc_toc_header h;
	int dir, junk, n, off, rc, trk;

	dir = (cmd == CMD_NEXT) ? 1 : -1;
	rc = ioctl (fd, CDIOREADTOCHEADER, &h);
	if (rc < 0)
		return (rc);

	n = h.ending_track - h.starting_track + 1;
	rc = status (&trk, &junk, &junk, &junk);
	if (rc < 0)
		return (-1);

	if (arg && *arg) {
		if (sscanf (arg, "%u", &off) != 1) {
		    warnx("invalid command argument");
		    return (0);
		} else
		    trk += off * dir;
	} else
		trk += dir;

	if (trk > h.ending_track)
		trk = 1;

	return (play_track (trk, 1, n, 1));
}