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
 int /*<<< orphan*/ * img ; 
 int /*<<< orphan*/  m ; 
 int /*<<< orphan*/  uiFreeImage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFreeTableModel (int /*<<< orphan*/ ) ; 

void freePage16(void)
{
	uiFreeTableModel(m);
	uiFreeImage(img[1]);
	uiFreeImage(img[0]);
}