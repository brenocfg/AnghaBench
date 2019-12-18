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
struct TYPE_3__ {char Key; int Up; scalar_t__ Modifiers; scalar_t__ Modifier; scalar_t__ ExtKey; } ;
typedef  TYPE_1__ uiAreaKeyEvent ;
typedef  int /*<<< orphan*/  uiAreaHandler ;
typedef  int /*<<< orphan*/  uiArea ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  swallowKeys ; 
 int uiCheckboxChecked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handlerKeyEvent(uiAreaHandler *ah, uiArea *a, uiAreaKeyEvent *e)
{
	char k[4];

	k[0] = '\'';
	k[1] = e->Key;
	k[2] = '\'';
	k[3] = '\0';
	if (e->Key == 0) {
		k[0] = '0';
		k[1] = '\0';
	}
	printf("key key:%s extkey:%d mod:%d mods:%d up:%d\n",
		k,
		(int) e->ExtKey,
		(int) e->Modifier,
		(int) e->Modifiers,
		e->Up);
	return uiCheckboxChecked(swallowKeys);
}