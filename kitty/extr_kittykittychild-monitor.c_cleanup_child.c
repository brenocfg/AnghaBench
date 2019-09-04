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
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 TYPE_1__* children ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hangup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
cleanup_child(ssize_t i) {
    close(children[i].fd);
    hangup(children[i].pid);
}