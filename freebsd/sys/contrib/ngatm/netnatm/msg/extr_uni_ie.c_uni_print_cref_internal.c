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
struct unicx {int dummy; } ;
struct uni_cref {scalar_t__ cref; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 scalar_t__ CREF_DUMMY ; 
 scalar_t__ CREF_GLOBAL ; 
 int /*<<< orphan*/  uni_print_entry (struct unicx*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_printf (struct unicx*,char*,...) ; 

__attribute__((used)) static void
uni_print_cref_internal(const struct uni_cref *cref, struct unicx *cx)
{
	uni_print_entry(cx, "cref", "%d.", cref->flag);
	if (cref->cref == CREF_GLOBAL)
		uni_printf(cx, "GLOBAL");
	else if (cref->cref == CREF_DUMMY)
		uni_printf(cx, "DUMMY");
	else
		uni_printf(cx, "%d", cref->cref);
}