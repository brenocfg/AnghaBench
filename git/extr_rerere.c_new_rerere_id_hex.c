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
struct rerere_id {int variant; int /*<<< orphan*/  collection; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_rerere_dir (char*) ; 
 struct rerere_id* xmalloc (int) ; 

__attribute__((used)) static struct rerere_id *new_rerere_id_hex(char *hex)
{
	struct rerere_id *id = xmalloc(sizeof(*id));
	id->collection = find_rerere_dir(hex);
	id->variant = -1; /* not known yet */
	return id;
}