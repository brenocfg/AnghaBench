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
typedef  int /*<<< orphan*/  u_long ;
struct protoent {int /*<<< orphan*/  p_proto; } ;
struct outproto {int /*<<< orphan*/  num; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 struct protoent* getprotobyname (char*) ; 
 int /*<<< orphan*/  optarg ; 
 struct outproto* protos ; 
 int /*<<< orphan*/  str2val (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 

struct outproto *
setproto(char *pname)
{
	struct outproto *proto;
	int i;

	for (i = 0; protos[i].name != NULL; i++) {
		if (strcasecmp(protos[i].name, pname) == 0) {
			break;
		}
	}
	proto = &protos[i];
	if (proto->name == NULL) {	/* generic handler */
		struct protoent *pe;
		u_long pnum;

		/* Determine the IP protocol number */
		if ((pe = getprotobyname(pname)) != NULL)
			pnum = pe->p_proto;
		else
			pnum = str2val(optarg, "proto number", 1, 255);
		proto->num = pnum;
	}
	return proto;
}