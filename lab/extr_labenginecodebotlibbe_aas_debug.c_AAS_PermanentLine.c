#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_2__ {int (* DebugLineCreate ) () ;int /*<<< orphan*/  (* DebugLineShow ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 TYPE_1__ botimport ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void AAS_PermanentLine(vec3_t start, vec3_t end, int color)
{
	int line;

	line = botimport.DebugLineCreate();
	botimport.DebugLineShow(line, start, end, color);
}