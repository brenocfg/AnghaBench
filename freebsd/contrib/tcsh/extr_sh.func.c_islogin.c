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

/* Variables and functions */
 int /*<<< orphan*/  ERR_NOTLOGIN ; 
 scalar_t__ chkstop ; 
 scalar_t__ loginsh ; 
 int /*<<< orphan*/  panystop (int /*<<< orphan*/ ) ; 
 scalar_t__ setintr ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
islogin(void)
{
    if (chkstop == 0 && setintr)
	panystop(0);
    if (loginsh)
	return;
    stderror(ERR_NOTLOGIN);
}