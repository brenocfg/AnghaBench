#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int punt; } ;
struct TYPE_4__ {TYPE_1__ sockrestart; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sockrestart_lock ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

bool sockrestart_should_restart_listen_wait() {
    lock(&sockrestart_lock);
    bool punt = current->sockrestart.punt;
    current->sockrestart.punt = false;
    unlock(&sockrestart_lock);
    return punt;
}