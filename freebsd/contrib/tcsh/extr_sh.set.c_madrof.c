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
struct varent {int /*<<< orphan*/  v_name; struct varent* v_left; struct varent* v_right; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 scalar_t__ Gmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct varent *
madrof(Char *pat, struct varent *vp)
{
    struct varent *vp1;

    for (vp = vp->v_left; vp; vp = vp->v_right) {
	if (vp->v_left && (vp1 = madrof(pat, vp)) != NULL)
	    return vp1;
	if (Gmatch(vp->v_name, pat))
	    return vp;
    }
    return vp;
}