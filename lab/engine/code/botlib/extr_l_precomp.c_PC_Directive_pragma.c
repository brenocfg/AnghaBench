#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  token_t ;
typedef  int /*<<< orphan*/  source_t ;

/* Variables and functions */
 scalar_t__ PC_ReadLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SourceWarning (int /*<<< orphan*/ *,char*) ; 
 int qtrue ; 

int PC_Directive_pragma(source_t *source)
{
	token_t token;

	SourceWarning(source, "#pragma directive not supported");
	while(PC_ReadLine(source, &token)) ;
	return qtrue;
}