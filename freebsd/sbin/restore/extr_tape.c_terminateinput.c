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
struct TYPE_2__ {scalar_t__ action; char* name; int /*<<< orphan*/  ino; scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ UNKNOWN ; 
 scalar_t__ USING ; 
 TYPE_1__ curfile ; 
 scalar_t__ gettingfile ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  maxino ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  restart ; 

__attribute__((used)) static void
terminateinput(void)
{

	if (gettingfile && curfile.action == USING) {
		printf("Warning: %s %s\n",
		    "End-of-input encountered while extracting", curfile.name);
	}
	curfile.name = "<name unknown>";
	curfile.action = UNKNOWN;
	curfile.mode = 0;
	curfile.ino = maxino;
	if (gettingfile) {
		gettingfile = 0;
		longjmp(restart, 1);
	}
}