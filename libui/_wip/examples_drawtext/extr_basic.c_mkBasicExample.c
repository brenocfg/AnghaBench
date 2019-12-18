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
struct example {char* name; int /*<<< orphan*/ * key; int /*<<< orphan*/ * mouse; int /*<<< orphan*/  draw; int /*<<< orphan*/  panel; } ;
struct TYPE_2__ {int /*<<< orphan*/  Align; int /*<<< orphan*/ * DefaultFont; int /*<<< orphan*/  String; } ;

/* Variables and functions */
 int /*<<< orphan*/  attrstr ; 
 struct example basicExample ; 
 int /*<<< orphan*/  defaultFont ; 
 int /*<<< orphan*/  draw ; 
 void* newCheckbox (char*) ; 
 int /*<<< orphan*/  panel ; 
 TYPE_1__ params ; 
 void* showExtents ; 
 void* showLineBounds ; 
 void* showLineGuides ; 
 int /*<<< orphan*/  text ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawTextAlignLeft ; 
 int /*<<< orphan*/  uiNewAttributedString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiNewVerticalBox () ; 

struct example *mkBasicExample(void)
{
	panel = uiNewVerticalBox();
	showExtents = newCheckbox("Show Layout Extents");
	showLineBounds = newCheckbox("Show Line Bounds");
	showLineGuides = newCheckbox("Show Line Guides");

	basicExample.name = "Basic Paragraph of Text";
	basicExample.panel = uiControl(panel);
	basicExample.draw = draw;
	basicExample.mouse = NULL;
	basicExample.key = NULL;

	attrstr = uiNewAttributedString(text);
	params.String = attrstr;
	params.DefaultFont = &defaultFont;
	params.Align = uiDrawTextAlignLeft;

	return &basicExample;
}