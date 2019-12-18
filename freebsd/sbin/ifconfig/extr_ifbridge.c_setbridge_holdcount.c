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
typedef  int u_long ;
struct ifbrparam {int ifbrp_txhc; } ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  param ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGSTXHC ; 
 scalar_t__ do_cmd (int,int /*<<< orphan*/ ,struct ifbrparam*,int,int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 scalar_t__ get_val (char const*,int*) ; 

__attribute__((used)) static void
setbridge_holdcount(const char *arg, int d, int s, const struct afswtch *afp)
{
	struct ifbrparam param;
	u_long val;

	if (get_val(arg, &val) < 0 || (val & ~0xff) != 0)
		errx(1, "invalid value: %s",  arg);

	param.ifbrp_txhc = val & 0xff;

	if (do_cmd(s, BRDGSTXHC, &param, sizeof(param), 1) < 0)
		err(1, "BRDGSTXHC %s",  arg);
}