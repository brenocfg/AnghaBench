#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread_data {int /*<<< orphan*/  ppp; int /*<<< orphan*/  hist; int /*<<< orphan*/  edit; } ;
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
struct TYPE_3__ {char* member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ HistEvent ;

/* Variables and functions */
 int /*<<< orphan*/  H_ENTER ; 
 int /*<<< orphan*/  InputHandler ; 
 int /*<<< orphan*/  REC_SHOW ; 
 scalar_t__ Receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_RESTART ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 char* SmartGets (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ ,TYPE_1__*,char const*,...) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int want_sem_post ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void *
Terminal(void *v)
{
    struct sigaction act, oact;
    struct thread_data *td;
    const char *l;
    int len;
#ifndef __OpenBSD__
    HistEvent hev = { 0, "" };
#endif

    act.sa_handler = InputHandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &act, &oact);

    td = (struct thread_data *)v;
    want_sem_post = 1;

    while ((l = SmartGets(td->edit, &len, td->ppp))) {
        if (len > 1)
#ifdef __OpenBSD__
            history(td->hist, H_ENTER, l);
#else
            history(td->hist, &hev, H_ENTER, l);
#endif
        write(td->ppp, l, len);
        if (Receive(td->ppp, REC_SHOW) != 0)
            break;
    }

    return NULL;
}