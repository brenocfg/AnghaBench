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
struct TYPE_4__ {int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  source_t ;

/* Variables and functions */
 int /*<<< orphan*/  PC_ReadToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PC_UnreadSourceToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int PC_CheckTokenString(source_t *source, char *string)
{
	token_t tok;

	if (!PC_ReadToken(source, &tok)) return qfalse;
	//if the token is available
	if (!strcmp(tok.string, string)) return qtrue;
	//
	PC_UnreadSourceToken(source, &tok);
	return qfalse;
}