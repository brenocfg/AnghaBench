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
struct varent {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 struct varent* adrof1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shvhed ; 
 int /*<<< orphan*/  udvar (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unsetv1 (struct varent*) ; 

void
unsetv(Char *var)
{
    struct varent *vp;

    if ((vp = adrof1(var, &shvhed)) == 0)
	udvar(var);
    unsetv1(vp);
}