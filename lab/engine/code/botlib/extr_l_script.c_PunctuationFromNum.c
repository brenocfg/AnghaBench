#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* punctuations; } ;
typedef  TYPE_2__ script_t ;
struct TYPE_4__ {char* p; int n; } ;

/* Variables and functions */

char *PunctuationFromNum(script_t *script, int num)
{
	int i;

	for (i = 0; script->punctuations[i].p; i++)
	{
		if (script->punctuations[i].n == num) return script->punctuations[i].p;
	} //end for
	return "unknown punctuation";
}