#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int Down; int Up; int Held1To64; int /*<<< orphan*/  AreaHeight; int /*<<< orphan*/  AreaWidth; void* Y; void* X; int /*<<< orphan*/  Modifiers; } ;
typedef  TYPE_1__ uiAreaMouseEvent ;
struct TYPE_10__ {TYPE_3__* ah; } ;
typedef  TYPE_2__ uiArea ;
typedef  int guint ;
typedef  void* gdouble ;
struct TYPE_11__ {int /*<<< orphan*/  (* MouseEvent ) (TYPE_3__*,TYPE_2__*,TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  GdkWindow ;

/* Variables and functions */
 int GDK_BUTTON1_MASK ; 
 int GDK_BUTTON2_MASK ; 
 int GDK_BUTTON3_MASK ; 
 int /*<<< orphan*/  loadAreaSize (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  toModifiers (int) ; 
 int translateModifiers (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void finishMouseEvent(uiArea *a, uiAreaMouseEvent *me, guint mb, gdouble x, gdouble y, guint state, GdkWindow *window)
{
	// on GTK+, mouse buttons 4-7 are for scrolling; if we got here, that's a mistake
	if (mb >= 4 && mb <= 7)
		return;
	// if the button ID >= 8, continue counting from 4, as in the MouseEvent spec
	if (me->Down >= 8)
		me->Down -= 4;
	if (me->Up >= 8)
		me->Up -= 4;

	state = translateModifiers(state, window);
	me->Modifiers = toModifiers(state);

	// the mb != # checks exclude the Up/Down button from Held
	me->Held1To64 = 0;
	if (mb != 1 && (state & GDK_BUTTON1_MASK) != 0)
		me->Held1To64 |= 1 << 0;
	if (mb != 2 && (state & GDK_BUTTON2_MASK) != 0)
		me->Held1To64 |= 1 << 1;
	if (mb != 3 && (state & GDK_BUTTON3_MASK) != 0)
		me->Held1To64 |= 1 << 2;
	// don't check GDK_BUTTON4_MASK or GDK_BUTTON5_MASK because those are for the scrolling buttons mentioned above
	// GDK expressly does not support any more buttons in the GdkModifierType; see https://git.gnome.org/browse/gtk+/tree/gdk/x11/gdkdevice-xi2.c#n763 (thanks mclasen in irc.gimp.net/#gtk+)

	// these are already in drawing space coordinates
	// the size of drawing space has the same value as the widget allocation
	// thanks to tristan in irc.gimp.net/#gtk+
	me->X = x;
	me->Y = y;

	loadAreaSize(a, &(me->AreaWidth), &(me->AreaHeight));

	(*(a->ah->MouseEvent))(a->ah, a, me);
}