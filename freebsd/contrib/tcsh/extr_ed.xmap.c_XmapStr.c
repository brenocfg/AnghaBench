#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct TYPE_7__ {TYPE_1__ str; } ;
typedef  TYPE_2__ XmapVal ;
struct TYPE_8__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
typedef  TYPE_3__ CStr ;

/* Variables and functions */

XmapVal *
XmapStr(CStr *str)
{
    static XmapVal xm;
    xm.str.len = str->len;
    xm.str.buf = str->buf;
    return &xm;
}