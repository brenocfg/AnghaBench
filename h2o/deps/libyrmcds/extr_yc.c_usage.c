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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void usage() {
    printf("Usage: yc "
           "[-h] [-v] [-d] [-t] [-s SERVER] [-p PORT] [-c COMPRESS] COMMAND ...\n\n"
           "Options:\n"
           "  -h      print help and exit.\n"
           "  -v      print version information.\n"
           "  -d      turn on debug messages.\n"
           "  -t      turn on text protocol mode.\n"
           "  -q      Use quiet commands, if possible.\n"
           "  -s      connect to SERVER.      Default: localhost\n"
           "  -p      TCP port number.        Default: 11211\n"
           "  -c      compression threshold.  Default: 16384\n\n"
           "Commands:\n"
           "  noop\n"
           "          ping the server.\n"
           "  get KEY\n"
           "          get an object.\n"
           "  getk KEY\n"
           "          get an object with key.\n"
           "  gat KEY EXPIRE\n"
           "          get and touch an object.\n"
           "  gatk KEY EXPIRE\n"
           "          get and touch an object with key.\n"
           "  lag KEY\n"
           "          lock and get an object.\n"
           "  lagk KEY\n"
           "          lock and get an object with key.\n"
           "  touch KEY EXPIRE\n"
           "          touch an object.\n"
           "  set KEY FILE [EXPIRE [FLAGS [CAS]]]\n"
           "          store FILE data.  If FILE is \"-\", stdin is used.\n"
           "  replace KEY FILE [EXPIRE [FLAGS [CAS]]]\n"
           "          update an existing object. FILE is the same as set.\n"
           "  add KEY FILE [EXPIRE [FLAGS [CAS]]]\n"
           "          create a new object. FILE is the same as set.\n"
           "  rau KEY FILE [EXPIRE [FLAGS]]\n"
           "          replace a locked object then unlock it.\n"
           "          Since this command always fails, do not use this.\n"
           "  incr KEY VALUE [INITIAL [EXPIRE]]\n"
           "          increments an exiting object's value by VALUE.\n"
           "          If INITIAL is given, new object is created when KEY\n"
           "          is not found.  EXPIRE is used only when an object is\n"
           "          created.\n"
           "  decr KEY VALUE [INITIAL [EXPIRE]]\n"
           "          decrements an exiting object's value by VALUE.\n"
           "          If INITIAL is given, new object is created when KEY\n"
           "          is not found.  EXPIRE is used only when an object is\n"
           "          created.\n"
           "  append KEY FILE\n"
           "          append FILE data  FILE is the same as set.\n"
           "  prepend KEY FILE\n"
           "          prepend FILE data  FILE is the same as set.\n"
           "  delete KEY\n"
           "          delete an object.\n"
           "  lock KEY\n"
           "          locks an object.\n"
           "  unlock KEY\n"
           "          this command always fails.  Do not use this.\n"
           "  unlockall\n"
           "          this command has no effect.\n"
           "  flush [DELAY]\n"
           "          flush all unlocked items immediately or after DELAY seconds.\n"
           "  stat [settings|items|sizes]\n"
           "          obtain general or specified statistics.\n"
           "  keys [PREFIX]\n"
           "          dump keys matching PREFIX.\n"
           "  version\n"
           "          shows the server version.\n"
           "  quit\n"
           "          just quits.  Not much interesting.\n"
        );
}