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
struct ttydevice {int dummy; } ;
struct physical {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 struct ttydevice* device2tty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ttydevice*) ; 
 int /*<<< orphan*/  tty_Offline (struct physical*) ; 

__attribute__((used)) static void
tty_Free(struct physical *p)
{
  struct ttydevice *dev = device2tty(p->handler);

  tty_Offline(p);	/* In case of emergency close()s */
  free(dev);
}