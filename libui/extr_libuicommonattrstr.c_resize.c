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
typedef  char uint16_t ;
struct TYPE_3__ {size_t len; char* s; size_t* u8tou16; size_t u16len; char* u16; size_t* u16tou8; } ;
typedef  TYPE_1__ uiAttributedString ;

/* Variables and functions */
 scalar_t__ uiprivRealloc (char*,int,char*) ; 

__attribute__((used)) static void resize(uiAttributedString *s, size_t u8, size_t u16)
{
	s->len = u8;
	s->s = (char *) uiprivRealloc(s->s, (s->len + 1) * sizeof (char), "char[] (uiAttributedString)");
	s->u8tou16 = (size_t *) uiprivRealloc(s->u8tou16, (s->len + 1) * sizeof (size_t), "size_t[] (uiAttributedString)");
	s->u16len = u16;
	s->u16 = (uint16_t *) uiprivRealloc(s->u16, (s->u16len + 1) * sizeof (uint16_t), "uint16_t[] (uiAttributedString)");
	s->u16tou8 = (size_t *) uiprivRealloc(s->u16tou8, (s->u16len + 1) * sizeof (size_t), "size_t[] (uiAttributedString)");
}