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
struct TYPE_2__ {int screenrows; int /*<<< orphan*/  screencols; int /*<<< orphan*/ * syntax; int /*<<< orphan*/ * filename; scalar_t__ dirty; int /*<<< orphan*/ * row; scalar_t__ numrows; scalar_t__ coloff; scalar_t__ rowoff; scalar_t__ cy; scalar_t__ cx; } ;

/* Variables and functions */
 TYPE_1__ E ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  exit (int) ; 
 int getWindowSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 

void initEditor(void) {
    E.cx = 0;
    E.cy = 0;
    E.rowoff = 0;
    E.coloff = 0;
    E.numrows = 0;
    E.row = NULL;
    E.dirty = 0;
    E.filename = NULL;
    E.syntax = NULL;
    if (getWindowSize(STDIN_FILENO,STDOUT_FILENO,
                      &E.screenrows,&E.screencols) == -1)
    {
        perror("Unable to query the screen for size (columns / rows)");
        exit(1);
    }
    E.screenrows -= 2; /* Get room for status bar. */
}