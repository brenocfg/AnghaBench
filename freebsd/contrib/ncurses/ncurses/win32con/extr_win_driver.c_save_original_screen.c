#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int X; int Y; } ;
struct TYPE_15__ {void* Right; void* Bottom; void* Left; void* Top; } ;
struct TYPE_14__ {int X; int Y; } ;
struct TYPE_16__ {TYPE_2__ srWindow; TYPE_1__ dwSize; } ;
struct TYPE_19__ {void* save_screen; TYPE_3__ SBI; } ;
struct TYPE_18__ {void* Right; void* Bottom; void* Left; void* Top; } ;
struct TYPE_17__ {int /*<<< orphan*/  hdl; } ;
typedef  TYPE_4__ TERMINAL_CONTROL_BLOCK ;
typedef  TYPE_5__ SMALL_RECT ;
typedef  void* SHORT ;
typedef  TYPE_6__ Properties ;
typedef  TYPE_7__ COORD ;
typedef  int /*<<< orphan*/  CHAR_INFO ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FreeAndNull (void*) ; 
 scalar_t__ GetLastError () ; 
 TYPE_6__* PropOf (TYPE_4__*) ; 
 scalar_t__ ReadConsoleOutput (int /*<<< orphan*/ ,void*,TYPE_7__,TYPE_7__,TYPE_5__*) ; 
 int /*<<< orphan*/  T (char*) ; 
 int TRUE ; 
 void* malloc (size_t) ; 

__attribute__((used)) static bool
save_original_screen(TERMINAL_CONTROL_BLOCK * TCB)
{
    bool result = FALSE;
    Properties *p = PropOf(TCB);
    COORD bufferSize;
    COORD bufferCoord;
    SMALL_RECT readRegion;
    size_t want;

    bufferSize.X = p->SBI.dwSize.X;
    bufferSize.Y = p->SBI.dwSize.Y;
    want = (size_t) (bufferSize.X * bufferSize.Y);

    if ((p->save_screen = malloc(want * sizeof(CHAR_INFO))) != 0) {
	bufferCoord.X = bufferCoord.Y = 0;

	readRegion.Top = 0;
	readRegion.Left = 0;
	readRegion.Bottom = (SHORT) (bufferSize.Y - 1);
	readRegion.Right = (SHORT) (bufferSize.X - 1);

	T(("... reading console buffer %dx%d into %d,%d - %d,%d at %d,%d",
	   bufferSize.Y, bufferSize.X,
	   readRegion.Top,
	   readRegion.Left,
	   readRegion.Bottom,
	   readRegion.Right,
	   bufferCoord.Y,
	   bufferCoord.X));

	if (ReadConsoleOutput(TCB->hdl,
			      p->save_screen,
			      bufferSize,
			      bufferCoord,
			      &readRegion)) {
	    result = TRUE;
	} else {
	    T((" error %#lx", (unsigned long) GetLastError()));
	    FreeAndNull(p->save_screen);

	    bufferSize.X = (SHORT) (p->SBI.srWindow.Right
				    - p->SBI.srWindow.Left + 1);
	    bufferSize.Y = (SHORT) (p->SBI.srWindow.Bottom
				    - p->SBI.srWindow.Top + 1);
	    want = (size_t) (bufferSize.X * bufferSize.Y);

	    if ((p->save_screen = malloc(want * sizeof(CHAR_INFO))) != 0) {
		bufferCoord.X = bufferCoord.Y = 0;

		readRegion.Top = p->SBI.srWindow.Top;
		readRegion.Left = p->SBI.srWindow.Left;
		readRegion.Bottom = p->SBI.srWindow.Bottom;
		readRegion.Right = p->SBI.srWindow.Right;

		T(("... reading console window %dx%d into %d,%d - %d,%d at %d,%d",
		   bufferSize.Y, bufferSize.X,
		   readRegion.Top,
		   readRegion.Left,
		   readRegion.Bottom,
		   readRegion.Right,
		   bufferCoord.Y,
		   bufferCoord.X));

		if (ReadConsoleOutput(TCB->hdl,
				      p->save_screen,
				      bufferSize,
				      bufferCoord,
				      &readRegion)) {
		    result = TRUE;
		} else {
		    T((" error %#lx", (unsigned long) GetLastError()));
		}
	    }
	}
    }

    T(("... save original screen contents %s", result ? "ok" : "err"));
    return result;
}