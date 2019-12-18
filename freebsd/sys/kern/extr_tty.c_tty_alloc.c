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
struct ttydevsw {int dummy; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 struct tty* tty_alloc_mutex (struct ttydevsw*,void*,int /*<<< orphan*/ *) ; 

struct tty *
tty_alloc(struct ttydevsw *tsw, void *sc)
{

	return (tty_alloc_mutex(tsw, sc, NULL));
}