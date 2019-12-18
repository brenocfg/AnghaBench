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
struct protoent {int p_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt_endprotoent () ; 
 struct protoent* bt_getprotoent () ; 
 int /*<<< orphan*/  bt_setprotoent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_stayopen ; 

struct protoent *
bt_getprotobynumber(int proto)
{
	struct protoent	*p;

	bt_setprotoent(proto_stayopen);
	while ((p = bt_getprotoent()) != NULL)
		if (p->p_proto == proto)
			break;
	bt_endprotoent();

	return (p);
}