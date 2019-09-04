#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ defined; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  EXTERN ; 
 int /*<<< orphan*/  GLOBAL ; 
 int /*<<< orphan*/  STATIC ; 
 TYPE_1__* afunc ; 
 int /*<<< orphan*/  array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* genident (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idtree (TYPE_1__*) ; 
 int /*<<< orphan*/  inttype ; 
 TYPE_1__* mksymbol (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcall (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  voidptype ; 
 int /*<<< orphan*/  voidtype ; 
 int /*<<< orphan*/  walk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bbentry(Symbol yylink, Symbol f) {
	static Symbol prologue;
	
	afunc = genident(STATIC, array(voidptype, 4, 0), GLOBAL);
	if (prologue == 0) {
		prologue = mksymbol(EXTERN, "_prologue", ftype(inttype, voidptype));
		prologue->defined = 0;
	}
	walk(vcall(prologue, voidtype, pointer(idtree(afunc)), pointer(idtree(yylink)), NULL), 0, 0);

}