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
 int /*<<< orphan*/  PC_ReadToken (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*) ; 
 int qfalse ; 
 int qtrue ; 

int PC_ExpectAnyToken(source_t *source, token_t *token)
{
	if (!PC_ReadToken(source, token))
	{
		SourceError(source, "couldn't read expected token");
		return qfalse;
	} //end if
	else
	{
		return qtrue;
	} //end else
}