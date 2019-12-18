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
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char CNL ; 
 int /*<<< orphan*/  ECHO ; 
 int /*<<< orphan*/  ECHONL ; 
 int /*<<< orphan*/  l ; 
 int ttydisc_echo_force (struct tty*,char,int) ; 

__attribute__((used)) static int
ttydisc_echo(struct tty *tp, char c, int quote)
{

	/*
	 * Only echo characters when ECHO is turned on, or ECHONL when
	 * the character is an unquoted newline.
	 */
	if (!CMP_FLAG(l, ECHO) &&
	    (!CMP_FLAG(l, ECHONL) || c != CNL || quote))
		return (0);

	return ttydisc_echo_force(tp, c, quote);
}