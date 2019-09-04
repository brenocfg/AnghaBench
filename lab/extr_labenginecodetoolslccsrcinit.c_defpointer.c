#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Value ;
struct TYPE_8__ {int /*<<< orphan*/  (* defconst ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* defaddress ) (TYPE_1__*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  size; } ;
struct TYPE_6__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 TYPE_5__* IR ; 
 int /*<<< orphan*/  P ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* voidptype ; 

void defpointer(Symbol p) {
	if (p) {
		(*IR->defaddress)(p);
		p->ref++;
	} else {
		static Value v;
		(*IR->defconst)(P, voidptype->size, v);
	}
}