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
struct sgttyb {int sg_flags; scalar_t__ sg_kill; scalar_t__ sg_erase; int /*<<< orphan*/  sg_ospeed; int /*<<< orphan*/  sg_ispeed; } ;

/* Variables and functions */
 int /*<<< orphan*/  B300 ; 
 int CHULDISC ; 
 int EVENP ; 
 int /*<<< orphan*/  I_POP ; 
 int /*<<< orphan*/  I_PUSH ; 
 int ODDP ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int RAW ; 
 int /*<<< orphan*/  TIOCEXCL ; 
 int /*<<< orphan*/  TIOCSETD ; 
 int /*<<< orphan*/  TIOCSETP ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,char*) ; 
 int open (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ usechuldisc ; 

int
openterm(
	char *dev
	)
{
	int s;
	struct sgttyb ttyb;

	if (debug)
	    (void) fprintf(stderr, "Doing open...");
	if ((s = open(dev, O_RDONLY, 0777)) < 0)
	    error("open(%s)", dev, "");
	if (debug)
	    (void) fprintf(stderr, "open okay\n");

	if (debug)
	    (void) fprintf(stderr, "Setting exclusive use...");
	if (ioctl(s, TIOCEXCL, (char *)0) < 0)
	    error("ioctl(TIOCEXCL)", "", "");
	if (debug)
	    (void) fprintf(stderr, "done\n");
	
	ttyb.sg_ispeed = ttyb.sg_ospeed = B300;
	ttyb.sg_erase = ttyb.sg_kill = 0;
	ttyb.sg_flags = EVENP|ODDP|RAW;
	if (debug)
	    (void) fprintf(stderr, "Setting baud rate et al...");
	if (ioctl(s, TIOCSETP, (char *)&ttyb) < 0)
	    error("ioctl(TIOCSETP, raw)", "", "");
	if (debug)
	    (void) fprintf(stderr, "done\n");

#ifdef CHULDISC
	if (usechuldisc) {
		int ldisc;

		if (debug)
		    (void) fprintf(stderr, "Switching to CHU ldisc...");
		ldisc = CHULDISC;
		if (ioctl(s, TIOCSETD, (char *)&ldisc) < 0)
		    error("ioctl(TIOCSETD, CHULDISC)", "", "");
		if (debug)
		    (void) fprintf(stderr, "okay\n");
	}
#endif
#ifdef STREAM
	if (usechuldisc) {

		if (debug)
		    (void) fprintf(stderr, "Poping off streams...");
		while (ioctl(s, I_POP, 0) >=0) ;
		if (debug)
		    (void) fprintf(stderr, "okay\n");
		if (debug)
		    (void) fprintf(stderr, "Pushing CHU stream...");
		if (ioctl(s, I_PUSH, "chu") < 0)
		    error("ioctl(I_PUSH, \"chu\")", "", "");
		if (debug)
		    (void) fprintf(stderr, "okay\n");
	}
#endif
	return s;
}