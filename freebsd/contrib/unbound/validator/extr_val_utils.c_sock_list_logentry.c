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
struct sock_list {scalar_t__ len; int /*<<< orphan*/  addr; } ;
typedef  enum verbosity_value { ____Placeholder_verbosity_value } verbosity_value ;

/* Variables and functions */
 int /*<<< orphan*/  log_addr (int,char const*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  verbose (int,char*,char const*) ; 

__attribute__((used)) static void
sock_list_logentry(enum verbosity_value v, const char* s, struct sock_list* p)
{
	if(p->len)
		log_addr(v, s, &p->addr, p->len);
	else	verbose(v, "%s cache", s);
}