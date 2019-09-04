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
typedef  int /*<<< orphan*/  uiEntry ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 char* uiEntryText (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiFreeText (char*) ; 

__attribute__((used)) static void entryChanged(uiEntry *e, void *data)
{
	char *text;

	text = uiEntryText(e);
	printf("%s entry changed: %s\n", (const char *) data, text);
	uiFreeText(text);
}