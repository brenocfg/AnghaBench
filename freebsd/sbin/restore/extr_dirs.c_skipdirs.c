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
struct TYPE_2__ {int mode; scalar_t__ ino; } ;

/* Variables and functions */
 int IFDIR ; 
 int IFMT ; 
 TYPE_1__ curfile ; 
 int /*<<< orphan*/  skipfile () ; 

void
skipdirs(void)
{

	while (curfile.ino && (curfile.mode & IFMT) == IFDIR) {
		skipfile();
	}
}