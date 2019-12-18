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
typedef  int /*<<< orphan*/  xdfile_t ;
struct TYPE_3__ {long (* find_func ) (char const*,long,char*,long,int /*<<< orphan*/ ) ;int /*<<< orphan*/  find_func_priv; } ;
typedef  TYPE_1__ xdemitconf_t ;

/* Variables and functions */
 long def_ff (char const*,long,char*,long,int /*<<< orphan*/ ) ; 
 long stub1 (char const*,long,char*,long,int /*<<< orphan*/ ) ; 
 long xdl_get_rec (int /*<<< orphan*/ *,long,char const**) ; 

__attribute__((used)) static long match_func_rec(xdfile_t *xdf, xdemitconf_t const *xecfg, long ri,
			   char *buf, long sz)
{
	const char *rec;
	long len = xdl_get_rec(xdf, ri, &rec);
	if (!xecfg->find_func)
		return def_ff(rec, len, buf, sz, xecfg->find_func_priv);
	return xecfg->find_func(rec, len, buf, sz, xecfg->find_func_priv);
}