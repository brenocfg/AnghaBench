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
struct auth_transfer {int /*<<< orphan*/ * chunks_last; struct auth_chunk* chunks_first; } ;
struct auth_chunk {struct auth_chunk* data; struct auth_chunk* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct auth_chunk*) ; 

__attribute__((used)) static void
auth_chunks_delete(struct auth_transfer* at)
{
	if(at->chunks_first) {
		struct auth_chunk* c, *cn;
		c = at->chunks_first;
		while(c) {
			cn = c->next;
			free(c->data);
			free(c);
			c = cn;
		}
	}
	at->chunks_first = NULL;
	at->chunks_last = NULL;
}