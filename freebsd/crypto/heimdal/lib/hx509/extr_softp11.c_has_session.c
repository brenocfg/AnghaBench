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
struct TYPE_2__ {scalar_t__ open_sessions; } ;

/* Variables and functions */
 TYPE_1__ soft_token ; 

__attribute__((used)) static const char *
has_session(void)
{
    return soft_token.open_sessions > 0 ? "yes" : "no";
}