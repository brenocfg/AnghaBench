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
struct tty_struct {int dummy; } ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int line_write (struct tty_struct*,unsigned char*,int) ; 

int line_put_char(struct tty_struct *tty, unsigned char ch)
{
	return line_write(tty, &ch, sizeof(ch));
}