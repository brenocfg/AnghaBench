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
struct nv {int dummy; } ;

/* Variables and functions */
 int HASTCTL_CMD_SETROLE ; 
 int SNMP_ERR_NOERROR ; 
 int hastctl (struct nv*,struct nv**) ; 
 int /*<<< orphan*/  nv_add_string (struct nv*,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_add_uint8 (struct nv*,int,char*) ; 
 struct nv* nv_alloc () ; 
 int /*<<< orphan*/  nv_free (struct nv*) ; 

__attribute__((used)) static int
set_role(const char *resource, int role)
{
	struct nv *nvin, *nvout;
	int error;

	nvin = nv_alloc();
	nv_add_string(nvin, resource, "resource%d", 0);
	nv_add_uint8(nvin, HASTCTL_CMD_SETROLE, "cmd");
	nv_add_uint8(nvin, role, "role");
	error = hastctl(nvin, &nvout);
	nv_free(nvin);
	if (error != 0)
		return (-1);
	nv_free(nvout);
	return (SNMP_ERR_NOERROR);
}