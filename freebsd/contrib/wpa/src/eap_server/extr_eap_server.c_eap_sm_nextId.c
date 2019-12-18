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
struct eap_sm {int lastId; } ;

/* Variables and functions */
 int rand () ; 

__attribute__((used)) static int eap_sm_nextId(struct eap_sm *sm, int id)
{
	if (id < 0) {
		/* RFC 3748 Ch 4.1: recommended to initialize Identifier with a
		 * random number */
		id = rand() & 0xff;
		if (id != sm->lastId)
			return id;
	}
	return (id + 1) & 0xff;
}