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
struct consdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAMBO_CONSOLE_WRITE ; 
 int /*<<< orphan*/  mambocall (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 

__attribute__((used)) static void
mambo_cnputc(struct consdev *cp, int c)
{
	char cbuf;

	cbuf = c;
	mambocall(MAMBO_CONSOLE_WRITE, &cbuf, 1UL, 1UL);
}