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
struct ead_msg_pong {char* name; int /*<<< orphan*/  auth_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  nid; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 struct ead_msg_pong* EAD_DATA (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int auth_type ; 
 TYPE_1__* msg ; 
 int nid ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct ead_msg_pong* pong ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  sid ; 

__attribute__((used)) static bool
handle_pong(void)
{
	struct ead_msg_pong *pong = EAD_DATA(msg, pong);
	int len = ntohl(msg->len) - sizeof(struct ead_msg_pong);

	if (len <= 0)
		return false;

	pong->name[len] = 0;
	auth_type = ntohs(pong->auth_type);
	if (nid == 0xffff)
		printf("%04x: %s\n", ntohs(msg->nid), pong->name);
	sid = msg->sid;
	return true;
}