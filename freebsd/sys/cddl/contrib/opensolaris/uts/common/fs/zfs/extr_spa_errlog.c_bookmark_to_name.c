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
struct TYPE_3__ {scalar_t__ zb_blkid; scalar_t__ zb_level; scalar_t__ zb_object; scalar_t__ zb_objset; } ;
typedef  TYPE_1__ zbookmark_phys_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bookmark_to_name(zbookmark_phys_t *zb, char *buf, size_t len)
{
	(void) snprintf(buf, len, "%llx:%llx:%llx:%llx",
	    (u_longlong_t)zb->zb_objset, (u_longlong_t)zb->zb_object,
	    (u_longlong_t)zb->zb_level, (u_longlong_t)zb->zb_blkid);
}