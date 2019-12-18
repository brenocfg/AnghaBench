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
struct tm {int tm_isdst; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; } ;

/* Variables and functions */
 scalar_t__ DSTMINUTES ; 
 int /*<<< orphan*/  MINSPERHOUR ; 
 int /*<<< orphan*/  normalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tm *
mkdst(
	struct tm *	tmp
	)
{
    /* jds */
    static struct tm tmbuf;

    tmbuf = *tmp;
    tmbuf.tm_isdst = 1;
    tmbuf.tm_min += DSTMINUTES;
    normalize(&tmbuf.tm_hour, &tmbuf.tm_min, MINSPERHOUR);
    return &tmbuf;
}