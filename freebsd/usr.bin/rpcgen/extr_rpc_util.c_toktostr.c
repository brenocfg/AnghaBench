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
struct TYPE_3__ {scalar_t__ kind; char const* str; } ;
typedef  TYPE_1__ token ;
typedef  scalar_t__ tok_kind ;

/* Variables and functions */
 scalar_t__ TOK_EOF ; 
 TYPE_1__* tokstrings ; 

__attribute__((used)) static const char *
toktostr(tok_kind kind)
{
	token *sp;

	for (sp = tokstrings; sp->kind != TOK_EOF && sp->kind != kind; sp++);
	return (sp->str);
}