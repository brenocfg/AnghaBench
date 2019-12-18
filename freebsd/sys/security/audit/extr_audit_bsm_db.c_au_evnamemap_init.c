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
struct TYPE_2__ {int /*<<< orphan*/  enl_head; } ;

/* Variables and functions */
 int EVNAMEMAP_HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  EVNAMEMAP_LOCK_INIT () ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  au_evnamemap_init_preload () ; 
 TYPE_1__* evnamemap_hash ; 

void
au_evnamemap_init(void)
{
	int i;

	EVNAMEMAP_LOCK_INIT();
	for (i = 0; i < EVNAMEMAP_HASH_TABLE_SIZE; i++)
		LIST_INIT(&evnamemap_hash[i].enl_head);
	au_evnamemap_init_preload();
}