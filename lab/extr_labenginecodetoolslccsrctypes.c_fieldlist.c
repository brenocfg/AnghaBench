#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_5__* Type ;
struct TYPE_10__ {TYPE_3__* sym; } ;
struct TYPE_11__ {TYPE_4__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  flist; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  Field ;

/* Variables and functions */

Field fieldlist(Type ty) {
	return ty->u.sym->u.s.flist;
}