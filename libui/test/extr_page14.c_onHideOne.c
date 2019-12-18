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
typedef  int /*<<< orphan*/  uiButton ;

/* Variables and functions */
 int /*<<< orphan*/  one ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControlHide (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void onHideOne(uiButton *b, void *data)
{
	uiControlHide(uiControl(one));
}