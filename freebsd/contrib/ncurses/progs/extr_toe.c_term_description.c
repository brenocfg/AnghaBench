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
struct TYPE_3__ {scalar_t__ term_names; } ;
typedef  TYPE_1__ TERMTYPE ;

/* Variables and functions */
 char* strrchr (scalar_t__,char) ; 

__attribute__((used)) static const char *
term_description(TERMTYPE *tp)
{
    const char *desc;

    if (tp->term_names == 0
	|| (desc = strrchr(tp->term_names, '|')) == 0
	|| (*++desc == '\0')) {
	desc = "(No description)";
    }

    return desc;
}