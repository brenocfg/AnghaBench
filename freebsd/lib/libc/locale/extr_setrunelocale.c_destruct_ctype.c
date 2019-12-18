#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xlocale_ctype {struct xlocale_ctype* runes; } ;

/* Variables and functions */
 struct xlocale_ctype _DefaultRuneLocale ; 
 int /*<<< orphan*/  free (struct xlocale_ctype*) ; 

__attribute__((used)) static void
destruct_ctype(void *v)
{
	struct xlocale_ctype *l = v;

	if (&_DefaultRuneLocale != l->runes)
		free(l->runes);
	free(l);
}