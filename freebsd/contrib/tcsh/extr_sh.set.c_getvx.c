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
struct varent {int /*<<< orphan*/  vec; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_NAME ; 
 int ERR_RANGE ; 
 struct varent* adrof (int /*<<< orphan*/ *) ; 
 int blklen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int) ; 
 int /*<<< orphan*/  udvar (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct varent *
getvx(Char *vp, int subscr)
{
    struct varent *v = adrof(vp);

    if (v == 0)
	udvar(vp);
    if (subscr < 1 || subscr > blklen(v->vec))
	stderror(ERR_NAME | ERR_RANGE);
    return (v);
}