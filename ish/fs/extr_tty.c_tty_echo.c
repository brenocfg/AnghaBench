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
struct tty {TYPE_2__* driver; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write ) (struct tty*,char const*,size_t,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tty*,char const*,size_t,int) ; 

__attribute__((used)) static void tty_echo(struct tty *tty, const char *data, size_t size) {
    tty->driver->ops->write(tty, data, size, false);
}