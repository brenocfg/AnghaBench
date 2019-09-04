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
struct TYPE_8__ {int /*<<< orphan*/  (* defsymbol ) (TYPE_2__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; TYPE_1__ x; } ;
typedef  TYPE_2__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  ANCHOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END ; 
 TYPE_5__* IR ; 
 int /*<<< orphan*/  code ; 
 int /*<<< orphan*/  href ; 
 int /*<<< orphan*/  print (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void emitSymRef(Symbol p) {
	(*IR->defsymbol)(p);
	ANCHOR(href,print("#%s", p->x.name)); BEGIN(code); print("%s", p->name); END; END;
}