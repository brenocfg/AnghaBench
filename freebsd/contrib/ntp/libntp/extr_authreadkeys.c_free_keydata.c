#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ seclen; struct TYPE_6__* next; struct TYPE_6__* keyacclist; } ;
typedef  TYPE_1__ KeyDataT ;
typedef  TYPE_1__ KeyAccT ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
free_keydata(
	KeyDataT *node
	)
{
	KeyAccT *kap;
	
	if (node) {
		while (node->keyacclist) {
			kap = node->keyacclist;
			node->keyacclist = kap->next;
			free(kap);
		}

		/* purge secrets from memory before free()ing it */
		memset(node, 0, sizeof(*node) + node->seclen);
		free(node);
	}
}