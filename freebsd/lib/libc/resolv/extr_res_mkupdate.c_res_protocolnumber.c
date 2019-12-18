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
struct valuelist {int dummy; } ;

/* Variables and functions */
 int findservice (char const*,struct valuelist**) ; 
 struct valuelist* protolist ; 
 int /*<<< orphan*/  res_buildprotolist () ; 

int
res_protocolnumber(const char *p) {
	if (protolist == (struct valuelist *)0)
		res_buildprotolist();
	return (findservice(p, &protolist));
}