#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  FIELD_CELL ;
typedef  TYPE_1__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/ * After_End_Of_Data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Buffer_Length (TYPE_1__*) ; 
 int /*<<< orphan*/ * Get_Start_Of_Data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myADDNSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
Undo_Justification(FIELD *field, WINDOW *win)
{
  FIELD_CELL *bp;
  int len;

  bp = Get_Start_Of_Data(field->buf, Buffer_Length(field));
  len = (int)(After_End_Of_Data(field->buf, Buffer_Length(field)) - bp);

  if (len > 0)
    {
      assert(win);
      wmove(win, 0, 0);
      myADDNSTR(win, bp, len);
    }
}