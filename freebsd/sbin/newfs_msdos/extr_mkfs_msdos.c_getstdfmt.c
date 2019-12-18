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
typedef  size_t u_int ;
struct bpb {int dummy; } ;
struct TYPE_3__ {struct bpb bpb; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t nitems (TYPE_1__*) ; 
 TYPE_1__* stdfmt ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
getstdfmt(const char *fmt, struct bpb *bpb)
{
    u_int x, i;

    x = nitems(stdfmt);
    for (i = 0; i < x && strcmp(fmt, stdfmt[i].name); i++);
    if (i == x) {
	warnx("%s: unknown standard format", fmt);
	return -1;
    }
    *bpb = stdfmt[i].bpb;
    return 0;
}