#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_2__ token ;
struct TYPE_7__ {int /*<<< orphan*/  co; } ;
struct TYPE_9__ {TYPE_1__ def; int /*<<< orphan*/  def_name; int /*<<< orphan*/  def_kind; } ;
typedef  TYPE_3__ definition ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_CONST ; 
 int /*<<< orphan*/  TOK_EQUAL ; 
 int /*<<< orphan*/  TOK_IDENT ; 
 int /*<<< orphan*/  TOK_STRCONST ; 
 int /*<<< orphan*/  scan (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  scan2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
def_const(definition *defp)
{
	token tok;

	defp->def_kind = DEF_CONST;
	scan(TOK_IDENT, &tok);
	defp->def_name = tok.str;
	scan(TOK_EQUAL, &tok);
	scan2(TOK_IDENT, TOK_STRCONST, &tok);
	defp->def.co = tok.str;
}