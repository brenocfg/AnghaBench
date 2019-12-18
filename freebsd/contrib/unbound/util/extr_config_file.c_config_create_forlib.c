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
struct config_file {int outgoing_num_ports; int outgoing_num_tcp; int msg_cache_size; int msg_cache_slabs; int rrset_cache_size; int rrset_cache_slabs; int infra_cache_slabs; int key_cache_size; int key_cache_slabs; int neg_cache_size; int val_log_level; int val_log_squelch; scalar_t__ minimal_responses; scalar_t__ donotquery_localhost; scalar_t__ use_syslog; scalar_t__ verbosity; int /*<<< orphan*/ * chrootdir; } ;

/* Variables and functions */
 struct config_file* config_create () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

struct config_file* config_create_forlib(void)
{
	struct config_file* cfg = config_create();
	if(!cfg) return NULL;
	/* modifications for library use, less verbose, less memory */
	free(cfg->chrootdir);
	cfg->chrootdir = NULL;
	cfg->verbosity = 0;
	cfg->outgoing_num_ports = 16; /* in library use, this is 'reasonable'
		and probably within the ulimit(maxfds) of the user */
	cfg->outgoing_num_tcp = 2;
	cfg->msg_cache_size = 1024*1024;
	cfg->msg_cache_slabs = 1;
	cfg->rrset_cache_size = 1024*1024;
	cfg->rrset_cache_slabs = 1;
	cfg->infra_cache_slabs = 1;
	cfg->use_syslog = 0;
	cfg->key_cache_size = 1024*1024;
	cfg->key_cache_slabs = 1;
	cfg->neg_cache_size = 100 * 1024;
	cfg->donotquery_localhost = 0; /* allow, so that you can ask a
		forward nameserver running on localhost */
	cfg->val_log_level = 2; /* to fill why_bogus with */
	cfg->val_log_squelch = 1;
	cfg->minimal_responses = 0;
	return cfg;
}