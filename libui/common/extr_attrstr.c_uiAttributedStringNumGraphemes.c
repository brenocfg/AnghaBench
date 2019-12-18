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
struct TYPE_6__ {TYPE_1__* graphemes; } ;
typedef  TYPE_2__ uiAttributedString ;
struct TYPE_5__ {size_t len; } ;

/* Variables and functions */
 int /*<<< orphan*/  recomputeGraphemes (TYPE_2__*) ; 

size_t uiAttributedStringNumGraphemes(uiAttributedString *s)
{
	recomputeGraphemes(s);
	return s->graphemes->len;
}