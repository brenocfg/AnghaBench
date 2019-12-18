#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_3__ {int /*<<< orphan*/ * buf; } ;
typedef  int /*<<< orphan*/  FIELD_CELL ;
typedef  TYPE_1__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/ * After_End_Of_Data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int getmaxx (int /*<<< orphan*/ *) ; 
 int getmaxy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  myADDNSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
Buffer_To_Window(const FIELD *field, WINDOW *win)
{
  int width, height;
  int y, x;
  int len;
  int row;
  FIELD_CELL *pBuffer;

  assert(win && field);

  getyx(win, y, x);
  width = getmaxx(win);
  height = getmaxy(win);

  for (row = 0, pBuffer = field->buf;
       row < height;
       row++, pBuffer += width)
    {
      if ((len = (int)(After_End_Of_Data(pBuffer, width) - pBuffer)) > 0)
	{
	  wmove(win, row, 0);
	  myADDNSTR(win, pBuffer, len);
	}
    }
  wmove(win, y, x);
}