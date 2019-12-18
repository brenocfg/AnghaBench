#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_4__ {char* key; scalar_t__ data; } ;
typedef  TYPE_1__ ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  FIND ; 
 scalar_t__ hsearch_r (TYPE_1__,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qid_map ; 

__attribute__((used)) static u_int32_t
qname_to_qid(char *qname)
{
	ENTRY	 item;
	ENTRY	*ret_item;
	uint32_t qid;
	
	/*
	 * We guarantee that same named queues on different interfaces
	 * have the same qid.
	 */
	item.key = qname;
	if (hsearch_r(item, FIND, &ret_item, &qid_map) == 0)
		return (0);

	qid = *(uint32_t *)ret_item->data;
	return (qid);
}