#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  a; int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; int /*<<< orphan*/  underlineColor; } ;
struct TYPE_7__ {int /*<<< orphan*/  features; TYPE_1__ color; int /*<<< orphan*/  underline; int /*<<< orphan*/  stretch; int /*<<< orphan*/  italic; int /*<<< orphan*/  weight; int /*<<< orphan*/  size; int /*<<< orphan*/  family; } ;
struct TYPE_8__ {int type; TYPE_2__ u; } ;
typedef  TYPE_3__ uiAttribute ;

/* Variables and functions */
#define  uiAttributeTypeBackground 137 
#define  uiAttributeTypeColor 136 
#define  uiAttributeTypeFamily 135 
#define  uiAttributeTypeFeatures 134 
#define  uiAttributeTypeItalic 133 
#define  uiAttributeTypeSize 132 
#define  uiAttributeTypeStretch 131 
#define  uiAttributeTypeUnderline 130 
#define  uiAttributeTypeUnderlineColor 129 
#define  uiAttributeTypeWeight 128 
 int uiprivOpenTypeFeaturesEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uiprivStricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int uiprivAttributeEqual(const uiAttribute *a, const uiAttribute *b)
{
	if (a == b)
		return 1;
	if (a->type != b->type)
		return 0;
	switch (a->type) {
	case uiAttributeTypeFamily:
		return uiprivStricmp(a->u.family, b->u.family);
	case uiAttributeTypeSize:
		// TODO is the use of == correct?
		return a->u.size == b->u.size;
	case uiAttributeTypeWeight:
		return a->u.weight == b->u.weight;
	case uiAttributeTypeItalic:
		return a->u.italic == b->u.italic;
	case uiAttributeTypeStretch:
		return a->u.stretch == b->u.stretch;
	case uiAttributeTypeUnderline:
		return a->u.underline == b->u.underline;
	case uiAttributeTypeUnderlineColor:
		if (a->u.color.underlineColor != b->u.color.underlineColor)
			return 0;
		// fall through
	case uiAttributeTypeColor:
	case uiAttributeTypeBackground:
		// TODO is the use of == correct?
		return (a->u.color.r == b->u.color.r) &&
			(a->u.color.g == b->u.color.g) &&
			(a->u.color.b == b->u.color.b) &&
			(a->u.color.a == b->u.color.a);
	case uiAttributeTypeFeatures:
		return uiprivOpenTypeFeaturesEqual(a->u.features, b->u.features);
	}
	// TODO should not be reached
	return 0;
}