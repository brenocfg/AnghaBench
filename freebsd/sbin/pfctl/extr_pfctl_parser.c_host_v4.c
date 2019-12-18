#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * addr32; } ;
struct TYPE_6__ {TYPE_1__ addr; } ;
struct TYPE_7__ {TYPE_2__ a; } ;
struct TYPE_8__ {TYPE_3__ v; } ;
struct node_host {struct node_host* tail; int /*<<< orphan*/ * next; TYPE_4__ addr; int /*<<< orphan*/  af; int /*<<< orphan*/ * ifname; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  ina ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 struct node_host* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int inet_net_pton (int /*<<< orphan*/ ,char const*,struct in_addr*,int) ; 
 int inet_pton (int /*<<< orphan*/ ,char const*,struct in_addr*) ; 
 int /*<<< orphan*/  memset (struct in_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_ipmask (struct node_host*,int) ; 
 int /*<<< orphan*/ * strrchr (char const*,char) ; 

struct node_host *
host_v4(const char *s, int mask)
{
	struct node_host	*h = NULL;
	struct in_addr		 ina;
	int			 bits = 32;

	memset(&ina, 0, sizeof(struct in_addr));
	if (strrchr(s, '/') != NULL) {
		if ((bits = inet_net_pton(AF_INET, s, &ina, sizeof(ina))) == -1)
			return (NULL);
	} else {
		if (inet_pton(AF_INET, s, &ina) != 1)
			return (NULL);
	}

	h = calloc(1, sizeof(struct node_host));
	if (h == NULL)
		err(1, "address: calloc");
	h->ifname = NULL;
	h->af = AF_INET;
	h->addr.v.a.addr.addr32[0] = ina.s_addr;
	set_ipmask(h, bits);
	h->next = NULL;
	h->tail = h;

	return (h);
}