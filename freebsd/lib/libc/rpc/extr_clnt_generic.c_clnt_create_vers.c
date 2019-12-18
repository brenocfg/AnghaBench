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
typedef  int /*<<< orphan*/  rpcvers_t ;
typedef  int /*<<< orphan*/  rpcprog_t ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/ * clnt_create_vers_timed (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

CLIENT *
clnt_create_vers(const char *hostname, rpcprog_t prog, rpcvers_t *vers_out,
	rpcvers_t vers_low, rpcvers_t vers_high, const char *nettype)
{

	return (clnt_create_vers_timed(hostname, prog, vers_out, vers_low,
				vers_high, nettype, NULL));
}