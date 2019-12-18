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
struct task {int dummy; } ;
struct siginfo_ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM_ ; 
 int /*<<< orphan*/  SI_TIMER_ ; 
 int /*<<< orphan*/  send_signal (struct task*,int /*<<< orphan*/ ,struct siginfo_) ; 

__attribute__((used)) static void itimer_notify(struct task *task) {
    struct siginfo_ info = {
        .code = SI_TIMER_,
    };
    send_signal(task, SIGALRM_, info);
}