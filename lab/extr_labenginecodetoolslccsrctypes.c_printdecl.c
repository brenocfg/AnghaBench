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
typedef  int /*<<< orphan*/  Type ;
struct TYPE_3__ {int sclass; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
#define  AUTO 132 
#define  ENUM 131 
#define  EXTERN 130 
#define  STATIC 129 
#define  TYPEDEF 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  typestring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void printdecl(Symbol p, Type ty) {
	switch (p->sclass) {
	case AUTO:
		fprint(stderr, "%s;\n", typestring(ty, p->name));
		break;
	case STATIC: case EXTERN:
		fprint(stderr, "%k %s;\n", p->sclass, typestring(ty, p->name));
		break;
	case TYPEDEF: case ENUM:
		break;
	default: assert(0);
	}
}