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
typedef  int uint64_t ;
struct mod_item {int size; int size6; struct chashbhead* main_ptr6; struct chashbhead* main_ptr; } ;
struct chashbhead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SLIST_INIT (struct chashbhead*) ; 
 struct chashbhead* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mod_item*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ta_prepare_mod_chash(void *ta_buf, uint64_t *pflags)
{
	struct mod_item *mi;
	struct chashbhead *head;
	int i;

	mi = (struct mod_item *)ta_buf;

	memset(mi, 0, sizeof(struct mod_item));
	mi->size = (*pflags >> 16) & 0xFFFF;
	mi->size6 = *pflags & 0xFFFF;
	if (mi->size > 0) {
		head = malloc(sizeof(struct chashbhead) * mi->size,
		    M_IPFW, M_WAITOK | M_ZERO);
		for (i = 0; i < mi->size; i++)
			SLIST_INIT(&head[i]);
		mi->main_ptr = head;
	}

	if (mi->size6 > 0) {
		head = malloc(sizeof(struct chashbhead) * mi->size6,
		    M_IPFW, M_WAITOK | M_ZERO);
		for (i = 0; i < mi->size6; i++)
			SLIST_INIT(&head[i]);
		mi->main_ptr6 = head;
	}

	return (0);
}