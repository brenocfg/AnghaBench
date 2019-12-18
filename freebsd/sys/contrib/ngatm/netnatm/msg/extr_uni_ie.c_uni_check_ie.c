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
struct TYPE_2__ {int /*<<< orphan*/  coding; } ;
union uni_ieall {TYPE_1__ h; } ;
struct unicx {int dummy; } ;
struct iedecl {int (* check ) (union uni_ieall*,struct unicx*) ;} ;
typedef  enum uni_ietype { ____Placeholder_uni_ietype } uni_ietype ;

/* Variables and functions */
 struct iedecl* GET_IEDECL (int,int /*<<< orphan*/ ) ; 
 int stub1 (union uni_ieall*,struct unicx*) ; 

int
uni_check_ie(enum uni_ietype code, union uni_ieall *ie, struct unicx *cx)
{
	const struct iedecl *iedecl = GET_IEDECL(code, ie->h.coding);

	if (iedecl != NULL)
		return (iedecl->check(ie, cx));
	else
		return (-1);
}