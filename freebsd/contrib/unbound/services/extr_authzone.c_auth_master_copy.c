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
struct auth_master {struct auth_master* host; struct auth_master* file; scalar_t__ list; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 scalar_t__ auth_addr_list_copy (scalar_t__) ; 
 int /*<<< orphan*/  free (struct auth_master*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ memdup (struct auth_master*,int) ; 
 void* strdup (struct auth_master*) ; 

__attribute__((used)) static struct auth_master*
auth_master_copy(struct auth_master* o)
{
	struct auth_master* m;
	if(!o) return NULL;
	m = (struct auth_master*)memdup(o, sizeof(*o));
	if(!m) {
		log_err("malloc failure");
		return NULL;
	}
	m->next = NULL;
	if(m->host) {
		m->host = strdup(m->host);
		if(!m->host) {
			free(m);
			log_err("malloc failure");
			return NULL;
		}
	}
	if(m->file) {
		m->file = strdup(m->file);
		if(!m->file) {
			free(m->host);
			free(m);
			log_err("malloc failure");
			return NULL;
		}
	}
	if(m->list) {
		m->list = auth_addr_list_copy(m->list);
		if(!m->list) {
			free(m->file);
			free(m->host);
			free(m);
			return NULL;
		}
	}
	return m;
}