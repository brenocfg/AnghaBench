#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sigset_t_ ;
struct TYPE_2__ {int has_saved_mask; int /*<<< orphan*/  blocked; int /*<<< orphan*/  saved_mask; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  sigmask_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sigmask_set_temp_unlocked(sigset_t_ mask) {
    current->saved_mask = current->blocked;
    current->has_saved_mask = true;
    sigmask_set(mask);
}