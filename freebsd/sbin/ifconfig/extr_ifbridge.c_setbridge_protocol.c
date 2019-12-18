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
struct ifbrparam {int ifbrp_proto; } ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  param ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGSPROTO ; 
 scalar_t__ do_cmd (int,int /*<<< orphan*/ ,struct ifbrparam*,int,int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static void
setbridge_protocol(const char *arg, int d, int s, const struct afswtch *afp)
{
	struct ifbrparam param;

	if (strcasecmp(arg, "stp") == 0) {
		param.ifbrp_proto = 0;
	} else if (strcasecmp(arg, "rstp") == 0) {
		param.ifbrp_proto = 2;
	} else {
		errx(1, "unknown stp protocol");
	}

	if (do_cmd(s, BRDGSPROTO, &param, sizeof(param), 1) < 0)
		err(1, "BRDGSPROTO %s",  arg);
}