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
struct TYPE_3__ {int u16len; int /*<<< orphan*/  u16tou8; } ;
typedef  TYPE_1__ uiAttributedString ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (size_t*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ uiprivAlloc (size_t,char*) ; 

size_t *uiprivAttributedStringCopyUTF16ToUTF8Table(const uiAttributedString *s, size_t *n)
{
	size_t *out;
	size_t nbytes;

	nbytes = (s->u16len + 1) * sizeof (size_t);
	*n = s->u16len;
	out = (size_t *) uiprivAlloc(nbytes, "size_t[] (uiAttributedString)");
	memmove(out, s->u16tou8, nbytes);
	return out;
}