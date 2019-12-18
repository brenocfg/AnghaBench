#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lc_messages_T {int dummy; } ;
struct xlocale_messages {struct lc_messages_T locale; } ;
typedef  TYPE_1__* locale_t ;
struct TYPE_3__ {scalar_t__* components; scalar_t__ using_messages_locale; } ;

/* Variables and functions */
 size_t XLC_MESSAGES ; 
 int /*<<< orphan*/  _C_messages_locale ; 

struct lc_messages_T *
__get_current_messages_locale(locale_t loc)
{
	return (loc->using_messages_locale
		? &((struct xlocale_messages *)loc->components[XLC_MESSAGES])->locale
		: (struct lc_messages_T *)&_C_messages_locale);
}