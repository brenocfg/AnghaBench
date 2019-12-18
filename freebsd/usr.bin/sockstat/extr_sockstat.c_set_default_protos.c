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
struct protoent {int /*<<< orphan*/  p_proto; } ;

/* Variables and functions */
 size_t default_numprotos ; 
 char** default_protos ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 struct protoent* getprotobyname (char const*) ; 
 int /*<<< orphan*/  init_protos (size_t) ; 
 size_t numprotos ; 
 int /*<<< orphan*/ * protos ; 

__attribute__((used)) static int set_default_protos(void)
{
	struct protoent *prot;
	const char *pname;
	size_t pindex;

	init_protos(default_numprotos);

	for (pindex = 0; pindex < default_numprotos; pindex++) {
		pname = default_protos[pindex];
		prot = getprotobyname(pname);
		if (prot == NULL)
			err(1, "getprotobyname: %s", pname);
		protos[pindex] = prot->p_proto;
	}
	numprotos = pindex;
	return (pindex);
}