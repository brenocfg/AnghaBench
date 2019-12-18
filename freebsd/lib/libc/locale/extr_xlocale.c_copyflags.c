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
typedef  TYPE_1__* locale_t ;
struct TYPE_4__ {int /*<<< orphan*/  using_messages_locale; int /*<<< orphan*/  using_time_locale; int /*<<< orphan*/  using_numeric_locale; int /*<<< orphan*/  using_monetary_locale; } ;

/* Variables and functions */

__attribute__((used)) static void
copyflags(locale_t new, locale_t old)
{
	new->using_monetary_locale = old->using_monetary_locale;
	new->using_numeric_locale = old->using_numeric_locale;
	new->using_time_locale = old->using_time_locale;
	new->using_messages_locale = old->using_messages_locale;
}