#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* buildBuffer; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ pack_t ;

/* Variables and functions */
 int /*<<< orphan*/  Z_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  unzClose (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void FS_FreePak(pack_t *thepak)
{
	unzClose(thepak->handle);
	Z_Free(thepak->buildBuffer);
	Z_Free(thepak);
}