#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _xlocale {int dummy; } ;
typedef  TYPE_2__* locale_t ;
struct TYPE_5__ {int /*<<< orphan*/  destructor; } ;
struct TYPE_6__ {int monetary_locale_changed; int numeric_locale_changed; TYPE_1__ header; } ;

/* Variables and functions */
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  destruct_locale ; 

__attribute__((used)) static locale_t
alloc_locale(void)
{
	locale_t new = calloc(sizeof(struct _xlocale), 1);

	new->header.destructor = destruct_locale;
	new->monetary_locale_changed = 1;
	new->numeric_locale_changed = 1;
	return (new);
}