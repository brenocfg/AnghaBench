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
struct termios {int dummy; } ;
struct physical {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int SpeedToUnsigned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfgetispeed (struct termios*) ; 
 int tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static unsigned
tty_Speed(struct physical *p)
{
  struct termios ios;

  if (tcgetattr(p->fd, &ios) == -1)
    return 0;

  return SpeedToUnsigned(cfgetispeed(&ios));
}