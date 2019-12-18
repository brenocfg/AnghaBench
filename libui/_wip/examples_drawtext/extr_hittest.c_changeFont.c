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
typedef  int /*<<< orphan*/  uiFontButton ;
struct TYPE_3__ {scalar_t__ Family; double Size; scalar_t__ Stretch; scalar_t__ Italic; scalar_t__ Weight; } ;

/* Variables and functions */
 TYPE_1__ defaultFont ; 
 int /*<<< orphan*/  fontButton ; 
 scalar_t__ fontFamily ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,double,int,int,int) ; 
 int /*<<< orphan*/  redraw () ; 
 int /*<<< orphan*/  uiFontButtonFont (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  uiFreeText (scalar_t__) ; 

__attribute__((used)) static void changeFont(uiFontButton *b, void *data)
{
	if (defaultFont.Family != fontFamily)
		uiFreeText(defaultFont.Family);
	// TODO rename defaultFont
	uiFontButtonFont(fontButton, &defaultFont);
	printf("{\n\tfamily: %s\n\tsize: %g\n\tweight: %d\n\titalic: %d\n\tstretch: %d\n}\n",
		defaultFont.Family,
		defaultFont.Size,
		(int) (defaultFont.Weight),
		(int) (defaultFont.Italic),
		(int) (defaultFont.Stretch));
	redraw();
}