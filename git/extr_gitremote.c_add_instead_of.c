#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rewrite {int instead_of_nr; TYPE_1__* instead_of; int /*<<< orphan*/  instead_of_alloc; } ;
struct TYPE_2__ {char const* s; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void add_instead_of(struct rewrite *rewrite, const char *instead_of)
{
	ALLOC_GROW(rewrite->instead_of, rewrite->instead_of_nr + 1, rewrite->instead_of_alloc);
	rewrite->instead_of[rewrite->instead_of_nr].s = instead_of;
	rewrite->instead_of[rewrite->instead_of_nr].len = strlen(instead_of);
	rewrite->instead_of_nr++;
}