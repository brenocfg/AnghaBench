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
struct TYPE_3__ {scalar_t__ (* find_func ) (char const*,int,char*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  find_func_priv; } ;
typedef  TYPE_1__ xdemitconf_t ;

/* Variables and functions */
 scalar_t__ isalpha (char const) ; 
 scalar_t__ stub1 (char const*,int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_funcname(xdemitconf_t *xecfg, const char *bol, const char *eol)
{
	if (xecfg) {
		char buf[1];
		return xecfg->find_func(bol, eol - bol, buf, 1,
					xecfg->find_func_priv) >= 0;
	}

	if (bol == eol)
		return 0;
	if (isalpha(*bol) || *bol == '_' || *bol == '$')
		return 1;
	return 0;
}