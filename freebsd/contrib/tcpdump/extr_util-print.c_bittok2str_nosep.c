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
typedef  int /*<<< orphan*/  u_int ;
struct tok {int dummy; } ;

/* Variables and functions */
 char* bittok2str_internal (struct tok const*,char const*,int /*<<< orphan*/ ,char*) ; 

char *
bittok2str_nosep(register const struct tok *lp, register const char *fmt,
	   register u_int v)
{
    return (bittok2str_internal(lp, fmt, v, ""));
}