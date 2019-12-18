#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ X; } ;
struct TYPE_5__ {scalar_t__ X; } ;
struct TYPE_6__ {TYPE_4__ dwCursorPosition; TYPE_1__ dwSize; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ CONSOLE_SCREEN_BUFFER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  FillConsoleOutputCharacterA (int /*<<< orphan*/ ,char,scalar_t__,TYPE_4__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  console ; 

__attribute__((used)) static void erase_in_line(void)
{
	CONSOLE_SCREEN_BUFFER_INFO sbi;
	DWORD dummy; /* Needed for Windows 7 (or Vista) regression */

	if (!console)
		return;

	GetConsoleScreenBufferInfo(console, &sbi);
	FillConsoleOutputCharacterA(console, ' ',
		sbi.dwSize.X - sbi.dwCursorPosition.X, sbi.dwCursorPosition,
		&dummy);
}