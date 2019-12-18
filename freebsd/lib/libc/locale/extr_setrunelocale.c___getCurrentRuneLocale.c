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
typedef  int /*<<< orphan*/  _RuneLocale ;
struct TYPE_2__ {int /*<<< orphan*/  const* runes; } ;

/* Variables and functions */
 TYPE_1__* XLOCALE_CTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __get_locale () ; 

const _RuneLocale *
__getCurrentRuneLocale(void)
{

	return (XLOCALE_CTYPE(__get_locale())->runes);
}