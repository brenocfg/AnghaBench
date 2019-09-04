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
typedef  int /*<<< orphan*/  uiOpenTypeFeatures ;
typedef  int /*<<< orphan*/  uiAttribute ;

/* Variables and functions */
 int /*<<< orphan*/  appendWithAttribute (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  attrstr ; 
 int /*<<< orphan*/  uiAttributedStringAppendUnattributed (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiFreeOpenTypeFeatures (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiNewAttributedString (char*) ; 
 int /*<<< orphan*/ * uiNewBackgroundAttribute (double,double,double,double) ; 
 int /*<<< orphan*/ * uiNewColorAttribute (double,double,double,double) ; 
 int /*<<< orphan*/ * uiNewFamilyAttribute (char*) ; 
 int /*<<< orphan*/ * uiNewFeaturesAttribute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiNewItalicAttribute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uiNewOpenTypeFeatures () ; 
 int /*<<< orphan*/ * uiNewSizeAttribute (int) ; 
 int /*<<< orphan*/ * uiNewStretchAttribute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uiNewUnderlineAttribute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uiNewUnderlineColorAttribute (int /*<<< orphan*/ ,double,double,double,double) ; 
 int /*<<< orphan*/ * uiNewWeightAttribute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiOpenTypeFeaturesAdd (int /*<<< orphan*/ *,char,char,char,char,int) ; 
 int /*<<< orphan*/  uiTextItalicItalic ; 
 int /*<<< orphan*/  uiTextStretchCondensed ; 
 int /*<<< orphan*/  uiTextWeightBold ; 
 int /*<<< orphan*/  uiUnderlineColorCustom ; 
 int /*<<< orphan*/  uiUnderlineColorSpelling ; 
 int /*<<< orphan*/  uiUnderlineDouble ; 
 int /*<<< orphan*/  uiUnderlineSingle ; 
 int /*<<< orphan*/  uiUnderlineSuggestion ; 

__attribute__((used)) static void makeAttributedString(void)
{
	uiAttribute *attr, *attr2;
	uiOpenTypeFeatures *otf;

	attrstr = uiNewAttributedString(
		"Drawing strings with libui is done with the uiAttributedString and uiDrawTextLayout objects.\n"
		"uiAttributedString lets you have a variety of attributes: ");

	attr = uiNewFamilyAttribute("Courier New");
	appendWithAttribute("font family", attr, NULL);
	uiAttributedStringAppendUnattributed(attrstr, ", ");

	attr = uiNewSizeAttribute(18);
	appendWithAttribute("font size", attr, NULL);
	uiAttributedStringAppendUnattributed(attrstr, ", ");

	attr = uiNewWeightAttribute(uiTextWeightBold);
	appendWithAttribute("font weight", attr, NULL);
	uiAttributedStringAppendUnattributed(attrstr, ", ");

	attr = uiNewItalicAttribute(uiTextItalicItalic);
	appendWithAttribute("font italicness", attr, NULL);
	uiAttributedStringAppendUnattributed(attrstr, ", ");

	attr = uiNewStretchAttribute(uiTextStretchCondensed);
	appendWithAttribute("font stretch", attr, NULL);
	uiAttributedStringAppendUnattributed(attrstr, ", ");

	attr = uiNewColorAttribute(0.75, 0.25, 0.5, 0.75);
	appendWithAttribute("text color", attr, NULL);
	uiAttributedStringAppendUnattributed(attrstr, ", ");

	attr = uiNewBackgroundAttribute(0.5, 0.5, 0.25, 0.5);
	appendWithAttribute("text background color", attr, NULL);
	uiAttributedStringAppendUnattributed(attrstr, ", ");


	attr = uiNewUnderlineAttribute(uiUnderlineSingle);
	appendWithAttribute("underline style", attr, NULL);
	uiAttributedStringAppendUnattributed(attrstr, ", ");

	uiAttributedStringAppendUnattributed(attrstr, "and ");
	attr = uiNewUnderlineAttribute(uiUnderlineDouble);
	attr2 = uiNewUnderlineColorAttribute(uiUnderlineColorCustom, 1.0, 0.0, 0.5, 1.0);
	appendWithAttribute("underline color", attr, attr2);
	uiAttributedStringAppendUnattributed(attrstr, ". ");

	uiAttributedStringAppendUnattributed(attrstr, "Furthermore, there are attributes allowing for ");
	attr = uiNewUnderlineAttribute(uiUnderlineSuggestion);
	attr2 = uiNewUnderlineColorAttribute(uiUnderlineColorSpelling, 0, 0, 0, 0);
	appendWithAttribute("special underlines for indicating spelling errors", attr, attr2);
	uiAttributedStringAppendUnattributed(attrstr, " (and other types of errors) ");

	uiAttributedStringAppendUnattributed(attrstr, "and control over OpenType features such as ligatures (for instance, ");
	otf = uiNewOpenTypeFeatures();
	uiOpenTypeFeaturesAdd(otf, 'l', 'i', 'g', 'a', 0);
	attr = uiNewFeaturesAttribute(otf);
	appendWithAttribute("afford", attr, NULL);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	uiOpenTypeFeaturesAdd(otf, 'l', 'i', 'g', 'a', 1);
	attr = uiNewFeaturesAttribute(otf);
	appendWithAttribute("afford", attr, NULL);
	uiFreeOpenTypeFeatures(otf);
	uiAttributedStringAppendUnattributed(attrstr, ").\n");

	uiAttributedStringAppendUnattributed(attrstr, "Use the controls opposite to the text to control properties of the text.");
}