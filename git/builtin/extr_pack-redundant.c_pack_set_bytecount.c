#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pack_list {struct pack_list* next; TYPE_1__* pack; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {scalar_t__ index_size; scalar_t__ pack_size; } ;

/* Variables and functions */

__attribute__((used)) static inline off_t pack_set_bytecount(struct pack_list *pl)
{
	off_t ret = 0;
	while (pl) {
		ret += pl->pack->pack_size;
		ret += pl->pack->index_size;
		pl = pl->next;
	}
	return ret;
}