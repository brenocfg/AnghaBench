#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uiButton ;

/* Variables and functions */
 int /*<<< orphan*/  description ; 
 int /*<<< orphan*/  parent ; 
 int /*<<< orphan*/  title ; 
 char* uiEntryText (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFreeText (char*) ; 
 int /*<<< orphan*/  uiMsgBox (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void msgBox(uiButton *b, void *data)
{
	char *t, *d;

	t = uiEntryText(title);
	d = uiEntryText(description);
	uiMsgBox(parent, t, d);
	uiFreeText(d);
	uiFreeText(t);
}