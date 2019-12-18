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
struct TYPE_3__ {int /*<<< orphan*/  cont_signal; int /*<<< orphan*/  stop_signal; scalar_t__ version; } ;
typedef  TYPE_1__ i3bar_child ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGSTOP ; 

__attribute__((used)) static void child_init(i3bar_child *child) {
    child->version = 0;
    child->stop_signal = SIGSTOP;
    child->cont_signal = SIGCONT;
}