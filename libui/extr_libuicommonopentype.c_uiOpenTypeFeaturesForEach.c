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
typedef  scalar_t__ (* uiOpenTypeFeaturesForEachFunc ) (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
struct TYPE_6__ {size_t len; struct feature* data; } ;
typedef  TYPE_1__ uiOpenTypeFeatures ;
typedef  scalar_t__ uiForEach ;
struct feature {int /*<<< orphan*/  value; int /*<<< orphan*/  d; int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ uiForEachStop ; 

void uiOpenTypeFeaturesForEach(const uiOpenTypeFeatures *otf, uiOpenTypeFeaturesForEachFunc f, void *data)
{
	size_t n;
	const struct feature *p;
	uiForEach ret;

	p = otf->data;
	for (n = 0; n < otf->len; n++) {
		ret = (*f)(otf, p->a, p->b, p->c, p->d, p->value, data);
		// TODO for all: require exact match?
		if (ret == uiForEachStop)
			return;
		p++;
	}
}