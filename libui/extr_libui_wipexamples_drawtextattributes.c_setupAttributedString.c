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
struct TYPE_3__ {char* Family; int Double; uintptr_t Value; double R; double G; double B; double A; int /*<<< orphan*/ * Features; void* Type; } ;
typedef  TYPE_1__ uiAttributeSpec ;

/* Variables and functions */
 void* addFeature (char*,int) ; 
 int /*<<< orphan*/  attrstr ; 
 size_t strlen (char const*) ; 
 void* uiAttributeBackground ; 
 void* uiAttributeColor ; 
 void* uiAttributeFamily ; 
 void* uiAttributeFeatures ; 
 void* uiAttributeItalic ; 
 void* uiAttributeSize ; 
 void* uiAttributeStretch ; 
 void* uiAttributeUnderline ; 
 void* uiAttributeUnderlineColor ; 
 void* uiAttributeWeight ; 
 int /*<<< orphan*/  uiAttributedStringAppendUnattributed (int /*<<< orphan*/ ,char const*) ; 
 size_t uiAttributedStringLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiAttributedStringSetAttribute (int /*<<< orphan*/ ,TYPE_1__*,size_t,size_t) ; 
 scalar_t__ uiDrawTextItalicItalic ; 
 scalar_t__ uiDrawTextStretchCondensed ; 
 scalar_t__ uiDrawTextWeightBold ; 
 uintptr_t uiDrawUnderlineColorCustom ; 
 uintptr_t uiDrawUnderlineColorSpelling ; 
 uintptr_t uiDrawUnderlineStyleDouble ; 
 void* uiDrawUnderlineStyleSingle ; 
 uintptr_t uiDrawUnderlineStyleSuggestion ; 
 int /*<<< orphan*/  uiNewAttributedString (char*) ; 
 int /*<<< orphan*/  uiOpenTypeFeaturesAdd (int /*<<< orphan*/ *,char,char,unsigned char,char,int) ; 

__attribute__((used)) static void setupAttributedString(void)
{
	uiAttributeSpec spec;
	size_t start, end;
	const char *next;
	uiOpenTypeFeatures *otf;
	int i;

	attrstr = uiNewAttributedString("uiAttributedString isn't just for plain text! It supports ");

	next = "multiple fonts";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFamily;
	spec.Family = "Courier New";
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "multiple sizes";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeSize;
	spec.Double = 18;
	uiAttributedStringSetAttribute(attrstr,
		&spec, start, end);

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "multiple weights";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeWeight;
	spec.Value = (uintptr_t) uiDrawTextWeightBold;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "multiple italics";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeItalic;
	spec.Value = (uintptr_t) uiDrawTextItalicItalic;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "multiple stretches";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeStretch;
	spec.Value = (uintptr_t) uiDrawTextStretchCondensed;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "multiple colors";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeColor;
	// Direct2D "Crimson" (#DC143C)
	spec.R = 0.8627450980392156;
	spec.G = 0.0784313725490196;
	spec.B = 0.2352941176470588;
	spec.A = 0.75;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "multiple backgrounds";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeBackground;
	// Direct2D "Peach Puff" (#FFDAB9)
	// TODO choose a darker color
	spec.R = 1.0;
	spec.G = 0.85490196078431372;
	spec.B = 0.7254901960784313;
	spec.A = 0.5;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "multiple";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeUnderline;
	spec.Value = uiDrawUnderlineStyleSingle;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " ");
	next = "underlines";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeUnderline;
	spec.Value = uiDrawUnderlineStyleDouble;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	spec.Type = uiAttributeUnderlineColor;
	spec.Value = uiDrawUnderlineColorCustom;
	spec.R = 0.5;
	spec.G = 0.0;
	spec.B = 1.0;
	spec.A = 1.0;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " (");
	next = "including underlines for spelling correction and the like";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeUnderline;
	spec.Value = uiDrawUnderlineStyleSuggestion;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	spec.Type = uiAttributeUnderlineColor;
	spec.Value = uiDrawUnderlineColorSpelling;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	// TODO randomize these ranges better
	// TODO make some overlap to test that
	// TODO also change colors to light foreground dark background
	next = "or any combination of the above";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeWeight;
	spec.Value = (uintptr_t) uiDrawTextWeightBold;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end - 8);
	spec.Type = uiAttributeItalic;
	spec.Value = (uintptr_t) uiDrawTextItalicItalic;
	uiAttributedStringSetAttribute(attrstr, &spec, start + 3, end - 4);
	spec.Type = uiAttributeColor;
	spec.R = 0.8627450980392156;
	spec.G = 0.0784313725490196;
	spec.B = 0.2352941176470588;
	spec.A = 0.75;
	uiAttributedStringSetAttribute(attrstr, &spec, start + 12, end);
	spec.Type = uiAttributeFamily;
	spec.Family = "Helvetica";
	uiAttributedStringSetAttribute(attrstr, &spec, start + 8, end - 1);
	spec.Type = uiAttributeBackground;
	spec.R = 1.0;
	spec.G = 0.85490196078431372;
	spec.B = 0.7254901960784313;
	spec.A = 0.5;
	uiAttributedStringSetAttribute(attrstr, &spec, start + 5, end - 7);
	spec.Type = uiAttributeUnderline;
	spec.Value = uiDrawUnderlineStyleSingle;
	uiAttributedStringSetAttribute(attrstr, &spec, start + 9, end - 1);

	// TODO rewrite this to talk about OpenTpe instead
	// TODO also shorten this to something more useful and that covers the general gist of things (and combines features arbitrarily like the previous demo) when we add a general OpenType demo (see the last TODO in this function)
	uiAttributedStringAppendUnattributed(attrstr, ". In addition, a variety of typographical features are available (depending on the chosen font) that can be switched on (or off, if the font enables them by default): ");

	next = "fi";
	uiAttributedStringAppendUnattributed(attrstr, "standard ligatures like f+i (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("liga", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	// note the use of LTR marks and RTL embeds to make sure the bidi algorithm doesn't kick in for our demonstration (it will produce incorrect results)
	// see also: https://www.w3.org/International/articles/inline-bidi-markup/#nomarkup
	next = "\xD9\x84\xD8\xA7";
	uiAttributedStringAppendUnattributed(attrstr, "required ligatures like \xE2\x80\xAB\xD9\x84\xE2\x80\xAC+\xE2\x80\xAB\xD8\xA7\xE2\x80\xAC (\xE2\x80\x8E\xE2\x80\xAB");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("rlig", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, "\xE2\x80\xAC)");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "ct";
	uiAttributedStringAppendUnattributed(attrstr, "discretionary/rare ligatures like c+t (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("dlig", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "the";
	uiAttributedStringAppendUnattributed(attrstr, "contextual ligatures like h+e in the (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("clig", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	otf = addFeature("hlig", 1);
	// This technically isn't what is meant by "historical ligatures", but Core Text's internal AAT-to-OpenType mapping says to include it, so we include it too
	uiOpenTypeFeaturesAdd(otf, 'h', 'i', 's', 't', 1);
	next = "\xC3\x9F";
	uiAttributedStringAppendUnattributed(attrstr, "historical ligatures like the decomposition of \xC3\x9F (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = otf;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	// TODO a different word than "writing"?
	next = "UnICasE wRITInG";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("unic", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "316";
	uiAttributedStringAppendUnattributed(attrstr, "proportional (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("pnum", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ") and tabular/monospaced (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("tnum", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ") numbers");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "123";
	uiAttributedStringAppendUnattributed(attrstr, "superscipts (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("sups", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "123";
	uiAttributedStringAppendUnattributed(attrstr, "subscripts (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("subs", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "1st";
	uiAttributedStringAppendUnattributed(attrstr, "ordinals (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("ordn", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "H2O";
	uiAttributedStringAppendUnattributed(attrstr, "scientific inferiors (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("sinf", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "2/3";
	uiAttributedStringAppendUnattributed(attrstr, "fraction forms (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
#if 0 /* TODO */
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFractionForms;
	spec.Value = uiAttributeFractionFormNone;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ", ");
#endif
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("afrc", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ", ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("frac", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "0";
	uiAttributedStringAppendUnattributed(attrstr, "slashed zeroes (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("zero", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("zero", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "\xCE\xA0\xCE\xA3";
	uiAttributedStringAppendUnattributed(attrstr, "mathematical greek (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("mgrk", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("mgrk", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "qwertyuiop\xE2\x80\xA2";
	uiAttributedStringAppendUnattributed(attrstr, "ornamental forms (");
	for (i = 1; i < 11; i++) {
		start = uiAttributedStringLen(attrstr);
		end = start + strlen(next);
		uiAttributedStringAppendUnattributed(attrstr, next);
		spec.Type = uiAttributeFeatures;
		spec.Features = addFeature("ornm", i);
		uiAttributedStringSetAttribute(attrstr, &spec, start, end);
		next = "\xE2\x80\xA2";
	}
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "g";
	uiAttributedStringAppendUnattributed(attrstr, "specific forms/alternates (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("aalt", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("aalt", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "ABCDEFGQWERTY";
	uiAttributedStringAppendUnattributed(attrstr, "titling capital forms (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("titl", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("titl", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "\xE7\x80\x86";
	uiAttributedStringAppendUnattributed(attrstr, "alternate Han character forms (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("jp78", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("jp83", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	otf = addFeature("onum", 0);
	// Core Text's internal AAT-to-OpenType mapping says to include this, so we include it too
	// TODO is it always set?
	uiOpenTypeFeaturesAdd(otf, 'l', 'n', 'u', 'm', 0);
	next = "0123456789";
	uiAttributedStringAppendUnattributed(attrstr, "lowercase numbers (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = otf;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	otf = addFeature("onum", 1);
	uiOpenTypeFeaturesAdd(otf, 'l', 'n', 'u', 'm', 1);
	spec.Features = otf;
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "\xE4\xBC\xBD";
	uiAttributedStringAppendUnattributed(attrstr, "hanja to hangul translation (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("hngl", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("hngl", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "\xE3\x81\x82";
	uiAttributedStringAppendUnattributed(attrstr, "annotated glyph forms (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("nalt", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("nalt", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("nalt", 4);			// AAT inverted circle
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "\xE3\x81\x82";
	uiAttributedStringAppendUnattributed(attrstr, "ruby forms of kana (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("ruby", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("ruby", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "now is the time";
	uiAttributedStringAppendUnattributed(attrstr, "italic forms of Latin letters in CJK fonts (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("ital", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("ital", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "{I} > {J}";
	uiAttributedStringAppendUnattributed(attrstr, "case-sensitive character forms, such as punctuation (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("case", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("case", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "ABC";
	uiAttributedStringAppendUnattributed(attrstr, "specialized spacing between uppercase letters (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("cpsp", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("cpsp", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "\xE3\x82\xB9\xE3\x83\x98\xE3\x83\x88";
	uiAttributedStringAppendUnattributed(attrstr, "alternate horizontal (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("hkna", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("hkna", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ") and vertical (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("vkna", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("vkna", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ") kana forms");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "g";
	uiAttributedStringAppendUnattributed(attrstr, "stylistic alternates (");
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	for (i = 1; i <= 20; i++) {
		char tag[4];

		tag[0] = 's';
		tag[1] = 's';
		tag[2] = '0';
		if (i >= 10)
			tag[2] = '1';
		tag[3] = (i % 10) + '0';		// TODO see how I wrote this elsewhere
		start = uiAttributedStringLen(attrstr);
		end = start + strlen(next);
		uiAttributedStringAppendUnattributed(attrstr, next);
		spec.Features = addFeature(tag, 1);
		uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	}
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "first";
	uiAttributedStringAppendUnattributed(attrstr, "contextual alternates (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("calt", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("calt", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "FONT";
	uiAttributedStringAppendUnattributed(attrstr, "swashes (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("swsh", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("swsh", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "Font";
	uiAttributedStringAppendUnattributed(attrstr, "contextual swashes (");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("cswh", 0);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, " vs. ");
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("cswh", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ")");

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "Small Caps";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("smcp", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ", ");
	next = "Petite Caps";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("pcap", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);

	uiAttributedStringAppendUnattributed(attrstr, ", ");

	next = "SMALL UPPERCASES";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("c2sp", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);
	uiAttributedStringAppendUnattributed(attrstr, ", and ");
	next = "PETITE UPPERCASES";
	start = uiAttributedStringLen(attrstr);
	end = start + strlen(next);
	uiAttributedStringAppendUnattributed(attrstr, next);
	spec.Type = uiAttributeFeatures;
	spec.Features = addFeature("c2pc", 1);
	uiAttributedStringSetAttribute(attrstr, &spec, start, end);

	uiAttributedStringAppendUnattributed(attrstr, ".");

	// TODO write a dedicated example for experimenting with typographic features like the one in gtk3-demo
}