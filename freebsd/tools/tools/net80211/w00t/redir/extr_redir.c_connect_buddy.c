#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_family; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct params {int s; TYPE_2__ dst; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  s_in ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int connect_buddy(struct params *p)
{
	struct sockaddr_in s_in;

	memset(&s_in, 0, sizeof(s_in));
	s_in.sin_family = PF_INET;
	s_in.sin_port = htons(p->port);
	s_in.sin_addr.s_addr = p->dst.s_addr;

	if ((p->s = socket(s_in.sin_family, SOCK_STREAM, IPPROTO_TCP)) == -1)
		return -1;

	if (connect(p->s, (struct sockaddr*) &s_in, sizeof(s_in)) == -1)
		return -1;

	return 0;
}