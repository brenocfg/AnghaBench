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
typedef  int /*<<< orphan*/  uiEditableCombobox ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* uiEditableComboboxText (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiFreeText (char*) ; 

__attribute__((used)) static void onECBChanged(uiEditableCombobox *c, void *data)
{
	char *t;

	t = uiEditableComboboxText(c);
	printf("%s combobox changed to %s\n",
		(char *) data,
		t);
	uiFreeText(t);
}