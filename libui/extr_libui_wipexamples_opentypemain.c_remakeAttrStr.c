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
typedef  int /*<<< orphan*/  uiOpenTypeFeatures ;
struct TYPE_3__ {int /*<<< orphan*/ * Features; int /*<<< orphan*/  Type; } ;
typedef  TYPE_1__ uiAttributeSpec ;

/* Variables and functions */
 int /*<<< orphan*/  area ; 
 int /*<<< orphan*/ * attrstr ; 
 int /*<<< orphan*/  nullFeatures ; 
 int /*<<< orphan*/  textEntry ; 
 int /*<<< orphan*/  uiAreaQueueRedrawAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiAttributeFeatures ; 
 int /*<<< orphan*/  uiAttributedStringLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiAttributedStringSetAttribute (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiCheckboxChecked (int /*<<< orphan*/ ) ; 
 char* uiEntryText (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFreeAttributedString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiFreeOpenTypeFeatures (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiFreeText (char*) ; 
 int /*<<< orphan*/ * uiNewAttributedString (char*) ; 
 int /*<<< orphan*/ * uiNewOpenTypeFeatures () ; 

__attribute__((used)) static void remakeAttrStr(void)
{
	char *text;
	uiOpenTypeFeatures *otf;
	uiAttributeSpec spec;

	if (attrstr != NULL)
		uiFreeAttributedString(attrstr);

	text = uiEntryText(textEntry);
	attrstr = uiNewAttributedString(text);
	uiFreeText(text);

	if (!uiCheckboxChecked(nullFeatures)) {
		otf = uiNewOpenTypeFeatures();
		// TODO
		spec.Type = uiAttributeFeatures;
		spec.Features = otf;
		uiAttributedStringSetAttribute(attrstr, &spec,
			0, uiAttributedStringLen(attrstr));
		// and uiAttributedString copied otf
		uiFreeOpenTypeFeatures(otf);
	}

	uiAreaQueueRedrawAll(area);
}