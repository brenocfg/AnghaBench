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
typedef  int u_char ;
struct protoent {int p_proto; } ;
typedef  int /*<<< orphan*/  ipfw_insn ;

/* Variables and functions */
 int /*<<< orphan*/  O_PROTO ; 
 int /*<<< orphan*/  fill_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct protoent* getprotobyname (char*) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static ipfw_insn *
add_proto0(ipfw_insn *cmd, char *av, u_char *protop)
{
	struct protoent *pe;
	char *ep;
	int proto;

	proto = strtol(av, &ep, 10);
	if (*ep != '\0' || proto <= 0) {
		if ((pe = getprotobyname(av)) == NULL)
			return NULL;
		proto = pe->p_proto;
	}

	fill_cmd(cmd, O_PROTO, 0, proto);
	*protop = proto;
	return cmd;
}