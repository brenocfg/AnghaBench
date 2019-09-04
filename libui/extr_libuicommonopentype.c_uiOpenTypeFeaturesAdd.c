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
typedef  void* uint32_t ;
struct TYPE_4__ {int len; int cap; struct feature* data; } ;
typedef  TYPE_1__ uiOpenTypeFeatures ;
struct feature {char a; char b; char c; char d; void* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  bytecount (int) ; 
 int /*<<< orphan*/  featurecmp ; 
 scalar_t__ find (struct feature*,TYPE_1__*) ; 
 struct feature mkkey (char,char,char,char) ; 
 int /*<<< orphan*/  qsort (struct feature*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ uiprivRealloc (struct feature*,int /*<<< orphan*/ ,char*) ; 

void uiOpenTypeFeaturesAdd(uiOpenTypeFeatures *otf, char a, char b, char c, char d, uint32_t value)
{
	struct feature *f;
	struct feature key;

	// replace existing value if any
	key = mkkey(a, b, c, d);
	f = (struct feature *) find(&key, otf);
	if (f != NULL) {
		f->value = value;
		return;
	}

	// if we got here, the tag is new
	if (otf->len == otf->cap) {
		otf->cap *= 2;
		otf->data = (struct feature *) uiprivRealloc(otf->data, bytecount(otf->cap), "struct feature[]");
	}
	f = otf->data + otf->len;
	f->a = a;
	f->b = b;
	f->c = c;
	f->d = d;
	f->value = value;
	// LONGTERM qsort here is overkill
	otf->len++;
	qsort(otf->data, otf->len, sizeof (struct feature), featurecmp);
}