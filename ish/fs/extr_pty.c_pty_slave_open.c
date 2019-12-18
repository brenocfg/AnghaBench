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
struct TYPE_2__ {scalar_t__ locked; int /*<<< orphan*/ * other; } ;
struct tty {TYPE_1__ pty; } ;

/* Variables and functions */
 int _EIO ; 

__attribute__((used)) static int pty_slave_open(struct tty *tty) {
    if (tty->pty.other == NULL)
        return _EIO;
    if (tty->pty.locked)
        return _EIO;
    return 0;
}