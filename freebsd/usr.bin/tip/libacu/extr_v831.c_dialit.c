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
struct vaconfig {scalar_t__ vc_name; int /*<<< orphan*/  vc_modem; int /*<<< orphan*/  vc_rack; } ;
struct termios {int c_cflag; int c_lflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT ; 
 int /*<<< orphan*/  AC ; 
 int /*<<< orphan*/  B2400 ; 
 int /*<<< orphan*/  ETX ; 
 int ICANON ; 
 int ISIG ; 
 int PARENB ; 
 int PARODD ; 
 int /*<<< orphan*/  SI ; 
 int /*<<< orphan*/  STX ; 
 int /*<<< orphan*/  TCIOFLUSH ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  cfsetispeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfsetospeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  pc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 char* sanitize (char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  tcflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  v831_disconnect () ; 
 struct vaconfig* vaconfig ; 

__attribute__((used)) static int
dialit(char *phonenum, char *acu)
{
        struct vaconfig *vp;
	struct termios cntrl;
        char c;
        int i;

        phonenum = sanitize(phonenum);
#ifdef DEBUG
        printf ("(dial phonenum=%s)\n", phonenum);
#endif
        if (*phonenum == '<' && phonenum[1] == 0)
                return ('Z');
	for (vp = vaconfig; vp->vc_name; vp++)
		if (strcmp(vp->vc_name, acu) == 0)
			break;
	if (vp->vc_name == 0) {
		printf("Unable to locate dialer (%s)\n", acu);
		return ('K');
	}
	tcgetattr(AC, &cntrl);
	cfsetospeed(&cntrl, B2400);
	cfsetispeed(&cntrl, B2400);
	cntrl.c_cflag |= PARODD | PARENB;
	cntrl.c_lflag &= ~(ISIG | ICANON);
	tcsetattr(AC, TCSANOW, &cntrl);
	tcflush(AC, TCIOFLUSH);
        pc(STX);
	pc(vp->vc_rack);
	pc(vp->vc_modem);
	while (*phonenum && *phonenum != '<')
		pc(*phonenum++);
        pc(SI);
	pc(ETX);
        sleep(1);
        i = read(AC, &c, 1);
#ifdef DEBUG
        printf("read %d chars, char=%c, errno %d\n", i, c, errno);
#endif
        if (i != 1)
		c = 'M';
        if (c == 'B' || c == 'G') {
                char cc, oc = c;

                pc(ABORT);
                read(AC, &cc, 1);
#ifdef DEBUG
                printf("abort response=%c\n", cc);
#endif
                c = oc;
                v831_disconnect();
        }
        close(AC);
#ifdef DEBUG
        printf("dialit: returns %c\n", c);
#endif
        return (c);
}