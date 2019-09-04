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
 int /*<<< orphan*/  uiMultilineEntry (void*) ; 
 int /*<<< orphan*/  uiMultilineEntryAppend (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void appendClicked(uiButton *b, void *data)
{
	uiMultilineEntryAppend(uiMultilineEntry(data), "append\n");
}