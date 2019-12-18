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
typedef  int /*<<< orphan*/  uiAttribute ;

/* Variables and functions */
 int /*<<< orphan*/  attrstr ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  uiAttributedStringAppendUnattributed (int /*<<< orphan*/ ,char const*) ; 
 size_t uiAttributedStringLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiAttributedStringSetAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,size_t) ; 

__attribute__((used)) static void appendWithAttribute(const char *what, uiAttribute *attr, uiAttribute *attr2)
{
	size_t start, end;

	start = uiAttributedStringLen(attrstr);
	end = start + strlen(what);
	uiAttributedStringAppendUnattributed(attrstr, what);
	uiAttributedStringSetAttribute(attrstr, attr, start, end);
	if (attr2 != NULL)
		uiAttributedStringSetAttribute(attrstr, attr2, start, end);
}