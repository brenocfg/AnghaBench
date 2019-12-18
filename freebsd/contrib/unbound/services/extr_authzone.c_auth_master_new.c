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
struct auth_master {struct auth_master* next; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  log_err (char*) ; 

__attribute__((used)) static struct auth_master*
auth_master_new(struct auth_master*** list)
{
	struct auth_master *m;
	m = (struct auth_master*)calloc(1, sizeof(*m));
	if(!m) {
		log_err("malloc failure");
		return NULL;
	}
	/* set first pointer to m, or next pointer of previous element to m */
	(**list) = m;
	/* store m's next pointer as future point to store at */
	(*list) = &(m->next);
	return m;
}