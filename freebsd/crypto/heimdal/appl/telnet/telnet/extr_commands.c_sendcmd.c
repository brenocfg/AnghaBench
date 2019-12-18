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
struct sendlist {int narg; char* name; int /*<<< orphan*/  what; scalar_t__ (* handler ) (char*,char*) ;scalar_t__ needconnect; scalar_t__ nbyte; } ;

/* Variables and functions */
 scalar_t__ Ambiguous (struct sendlist*) ; 
 struct sendlist* GETSEND (char*) ; 
 int /*<<< orphan*/  IAC ; 
 int /*<<< orphan*/  NET2ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NETROOM () ; 
 int /*<<< orphan*/  connected ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printoption (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quit () ; 
 scalar_t__ send_help () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stub1 (char*,char*) ; 

__attribute__((used)) static int
sendcmd(int argc, char **argv)
{
    int count;		/* how many bytes we are going to need to send */
    int i;
    struct sendlist *s;	/* pointer to current command */
    int success = 0;
    int needconnect = 0;

    if (argc < 2) {
	printf("need at least one argument for 'send' command\r\n");
	printf("'send ?' for help\r\n");
	return 0;
    }
    /*
     * First, validate all the send arguments.
     * In addition, we see how much space we are going to need, and
     * whether or not we will be doing a "SYNCH" operation (which
     * flushes the network queue).
     */
    count = 0;
    for (i = 1; i < argc; i++) {
	s = GETSEND(argv[i]);
	if (s == 0) {
	    printf("Unknown send argument '%s'\r\n'send ?' for help.\r\n",
			argv[i]);
	    return 0;
	} else if (Ambiguous(s)) {
	    printf("Ambiguous send argument '%s'\r\n'send ?' for help.\r\n",
			argv[i]);
	    return 0;
	}
	if (i + s->narg >= argc) {
	    fprintf(stderr,
	    "Need %d argument%s to 'send %s' command.  'send %s ?' for help.\r\n",
		s->narg, s->narg == 1 ? "" : "s", s->name, s->name);
	    return 0;
	}
	count += s->nbyte;
	if (s->handler == send_help) {
	    send_help();
	    return 0;
	}

	i += s->narg;
	needconnect += s->needconnect;
    }
    if (!connected && needconnect) {
	printf("?Need to be connected first.\r\n");
	printf("'send ?' for help\r\n");
	return 0;
    }
    /* Now, do we have enough room? */
    if (NETROOM() < count) {
	printf("There is not enough room in the buffer TO the network\r\n");
	printf("to process your request.  Nothing will be done.\r\n");
	printf("('send synch' will throw away most data in the network\r\n");
	printf("buffer, if this might help.)\r\n");
	return 0;
    }
    /* OK, they are all OK, now go through again and actually send */
    count = 0;
    for (i = 1; i < argc; i++) {
	if ((s = GETSEND(argv[i])) == 0) {
	    fprintf(stderr, "Telnet 'send' error - argument disappeared!\r\n");
	    quit();
	    /*NOTREACHED*/
	}
	if (s->handler) {
	    count++;
	    success += (*s->handler)((s->narg > 0) ? argv[i+1] : 0,
				  (s->narg > 1) ? argv[i+2] : 0);
	    i += s->narg;
	} else {
	    NET2ADD(IAC, s->what);
	    printoption("SENT", IAC, s->what);
	}
    }
    return (count == success);
}