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
struct suj_ino {int si_skipparent; int /*<<< orphan*/  si_ino; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOTDOT_OFFSET ; 
 scalar_t__ ino_isat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void
ino_setskip(struct suj_ino *sino, ino_t parent)
{
	int isdot;
	int mode;

	if (ino_isat(sino->si_ino, DOTDOT_OFFSET, parent, &mode, &isdot))
		sino->si_skipparent = 1;
}