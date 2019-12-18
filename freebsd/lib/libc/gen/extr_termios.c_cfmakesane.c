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
struct termios {int /*<<< orphan*/  c_cc; void* c_ospeed; void* c_ispeed; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_iflag; int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTYDEF_CFLAG ; 
 int /*<<< orphan*/  TTYDEF_IFLAG ; 
 int /*<<< orphan*/  TTYDEF_LFLAG ; 
 int /*<<< orphan*/  TTYDEF_OFLAG ; 
 void* TTYDEF_SPEED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttydefchars ; 

void
cfmakesane(struct termios *t)
{

	t->c_cflag = TTYDEF_CFLAG;
	t->c_iflag = TTYDEF_IFLAG;
	t->c_lflag = TTYDEF_LFLAG;
	t->c_oflag = TTYDEF_OFLAG;
	t->c_ispeed = TTYDEF_SPEED;
	t->c_ospeed = TTYDEF_SPEED;
	memcpy(&t->c_cc, ttydefchars, sizeof ttydefchars);
}