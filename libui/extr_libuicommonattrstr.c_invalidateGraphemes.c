#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* graphemes; } ;
typedef  TYPE_1__ uiAttributedString ;
struct TYPE_5__ {struct TYPE_5__* graphemesToPoints; struct TYPE_5__* pointsToGraphemes; } ;

/* Variables and functions */
 int /*<<< orphan*/  uiprivFree (TYPE_2__*) ; 

__attribute__((used)) static void invalidateGraphemes(uiAttributedString *s)
{
	if (s->graphemes == NULL)
		return;
	uiprivFree(s->graphemes->pointsToGraphemes);
	uiprivFree(s->graphemes->graphemesToPoints);
	uiprivFree(s->graphemes);
	s->graphemes = NULL;
}