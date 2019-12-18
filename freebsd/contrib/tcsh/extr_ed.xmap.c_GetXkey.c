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
typedef  int /*<<< orphan*/  XmapVal ;
typedef  int /*<<< orphan*/  CStr ;

/* Variables and functions */
 int TraverseMap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Xmap ; 

int
GetXkey(CStr *ch, XmapVal *val)
{
    return (TraverseMap(Xmap, ch, val));
}