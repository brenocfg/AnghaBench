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
struct TYPE_4__ {int drows; scalar_t__ dcols; scalar_t__ cols; int just; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  FIELD_CELL ;
typedef  TYPE_1__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/ * After_End_Of_Data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Buffer_Length (TYPE_1__*) ; 
 int /*<<< orphan*/ * Get_Start_Of_Data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  JUSTIFY_CENTER 130 
#define  JUSTIFY_LEFT 129 
#define  JUSTIFY_RIGHT 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  myADDNSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
Perform_Justification(FIELD *field, WINDOW *win)
{
  FIELD_CELL *bp;
  int len;
  int col = 0;

  bp = Get_Start_Of_Data(field->buf, Buffer_Length(field));
  len = (int)(After_End_Of_Data(field->buf, Buffer_Length(field)) - bp);

  if (len > 0)
    {
      assert(win && (field->drows == 1) && (field->dcols == field->cols));

      switch (field->just)
	{
	case JUSTIFY_LEFT:
	  break;
	case JUSTIFY_CENTER:
	  col = (field->cols - len) / 2;
	  break;
	case JUSTIFY_RIGHT:
	  col = field->cols - len;
	  break;
	default:
	  break;
	}

      wmove(win, 0, col);
      myADDNSTR(win, bp, len);
    }
}