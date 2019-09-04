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
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  Line ;

/* Variables and functions */
 int /*<<< orphan*/ * unicode_in_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlimit_for_line (int /*<<< orphan*/ *) ; 

PyObject *
line_as_unicode(Line* self) {
    return unicode_in_range(self, 0, xlimit_for_line(self), true, 0);
}