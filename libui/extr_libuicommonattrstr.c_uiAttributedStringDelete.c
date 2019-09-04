#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {size_t* u8tou16; size_t* s; size_t len; size_t* u16; size_t u16len; size_t* u16tou8; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ uiAttributedString ;

/* Variables and functions */
 int /*<<< orphan*/  invalidateGraphemes (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (size_t*,size_t*,size_t) ; 
 int /*<<< orphan*/  onCodepointBoundary (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  resize (TYPE_1__*,size_t,size_t) ; 
 int /*<<< orphan*/  uiprivAttrListRemoveCharacters (int /*<<< orphan*/ ,size_t,size_t) ; 

void uiAttributedStringDelete(uiAttributedString *s, size_t start, size_t end)
{
	size_t start16, end16;
	size_t count, count16;
	size_t i;

	if (!onCodepointBoundary(s, start)) {
		// TODO
	}
	if (!onCodepointBoundary(s, end)) {
		// TODO
	}

	count = end - start;
	start16 = s->u8tou16[start];
	end16 = s->u8tou16[end];
	count16 = end16 - start16;

	invalidateGraphemes(s);

	// overwrite old characters
	memmove(
		s->s + start,
		s->s + end,
		(s->len - end) * sizeof (char));
	memmove(
		s->u16 + start16,
		s->u16 + end16,
		(s->u16len - end16) * sizeof (uint16_t));
	// note the + 1 for these; we want to copy the terminating null too
	memmove(
		s->u8tou16 + start,
		s->u8tou16 + end,
		(s->len - end + 1) * sizeof (size_t));
	memmove(
		s->u16tou8 + start16,
		s->u16tou8 + end16,
		(s->u16len - end16 + 1) * sizeof (size_t));

	// update the conversion tables
	// note the use of <= to include the null terminator
	for (i = 0; i <= (s->len - end); i++)
		s->u8tou16[start + i] -= count16;
	for (i = 0; i <= (s->u16len - end16); i++)
		s->u16tou8[start16 + i] -= count;

	// null-terminate the string
	s->s[start + (s->len - end)] = 0;
	s->u16[start16 + (s->u16len - end16)] = 0;

	// fix up attributes
	uiprivAttrListRemoveCharacters(s->attrs, start, end);

	// and finally resize
	resize(s, s->len - count, s->u16len - count16);
}