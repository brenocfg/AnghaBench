#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; struct feature* data; } ;
typedef  TYPE_1__ uiOpenTypeFeatures ;
struct feature {int dummy; } ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  bytecount (size_t) ; 
 scalar_t__ find (struct feature*,TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (struct feature*,struct feature*,int /*<<< orphan*/ ) ; 
 struct feature mkkey (char,char,char,char) ; 

void uiOpenTypeFeaturesRemove(uiOpenTypeFeatures *otf, char a, char b, char c, char d)
{
	struct feature *f;
	struct feature key;
	ptrdiff_t index;
	size_t count;

	key = mkkey(a, b, c, d);
	f = (struct feature *) find(&key, otf);
	if (f == NULL)
		return;

	index = f - otf->data;
	count = otf->len - index - 1;
	memmove(f + 1, f, bytecount(count));
	otf->len--;
}