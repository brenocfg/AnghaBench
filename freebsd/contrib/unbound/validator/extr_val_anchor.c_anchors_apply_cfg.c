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
struct val_anchors {int /*<<< orphan*/  lock; struct trust_anchor* dlv_anchor; } ;
struct trust_anchor {int dummy; } ;
struct config_strlist {scalar_t__* str; struct config_strlist* next; } ;
struct config_file {scalar_t__* dlv_anchor_file; scalar_t__* chrootdir; struct config_strlist* auto_trust_anchor_file_list; struct config_strlist* dlv_anchor_list; struct config_strlist* trust_anchor_list; struct config_strlist* trusted_keys_file_list; struct config_strlist* trust_anchor_file_list; struct config_strlist* domain_insecure; scalar_t__ insecure_lan_zones; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ VERB_ALGO ; 
 int /*<<< orphan*/  anchor_insert_insecure (struct val_anchors*,char const*) ; 
 int /*<<< orphan*/  anchor_read_bind_file_wild (struct val_anchors*,int /*<<< orphan*/ *,char*) ; 
 struct trust_anchor* anchor_read_file (struct val_anchors*,int /*<<< orphan*/ *,char*,int) ; 
 struct trust_anchor* anchor_store_str (struct val_anchors*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  anchors_assemble_rrsets (struct val_anchors*) ; 
 char** as112_zones ; 
 int /*<<< orphan*/  autr_debug_print (struct val_anchors*) ; 
 int /*<<< orphan*/  autr_read_file (struct val_anchors*,char*) ; 
 int /*<<< orphan*/  init_parents (struct val_anchors*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 int /*<<< orphan*/  sldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sldns_buffer_new (int) ; 
 int /*<<< orphan*/  strlen (scalar_t__*) ; 
 scalar_t__ strncmp (char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 

int 
anchors_apply_cfg(struct val_anchors* anchors, struct config_file* cfg)
{
	struct config_strlist* f;
	const char** zstr;
	char* nm;
	sldns_buffer* parsebuf = sldns_buffer_new(65535);
	if(cfg->insecure_lan_zones) {
		for(zstr = as112_zones; *zstr; zstr++) {
			if(!anchor_insert_insecure(anchors, *zstr)) {
				log_err("error in insecure-lan-zones: %s", *zstr);
				sldns_buffer_free(parsebuf);
				return 0;
			}
		}
	}
	for(f = cfg->domain_insecure; f; f = f->next) {
		if(!f->str || f->str[0] == 0) /* empty "" */
			continue;
		if(!anchor_insert_insecure(anchors, f->str)) {
			log_err("error in domain-insecure: %s", f->str);
			sldns_buffer_free(parsebuf);
			return 0;
		}
	}
	for(f = cfg->trust_anchor_file_list; f; f = f->next) {
		if(!f->str || f->str[0] == 0) /* empty "" */
			continue;
		nm = f->str;
		if(cfg->chrootdir && cfg->chrootdir[0] && strncmp(nm,
			cfg->chrootdir, strlen(cfg->chrootdir)) == 0)
			nm += strlen(cfg->chrootdir);
		if(!anchor_read_file(anchors, parsebuf, nm, 0)) {
			log_err("error reading trust-anchor-file: %s", f->str);
			sldns_buffer_free(parsebuf);
			return 0;
		}
	}
	for(f = cfg->trusted_keys_file_list; f; f = f->next) {
		if(!f->str || f->str[0] == 0) /* empty "" */
			continue;
		nm = f->str;
		if(cfg->chrootdir && cfg->chrootdir[0] && strncmp(nm,
			cfg->chrootdir, strlen(cfg->chrootdir)) == 0)
			nm += strlen(cfg->chrootdir);
		if(!anchor_read_bind_file_wild(anchors, parsebuf, nm)) {
			log_err("error reading trusted-keys-file: %s", f->str);
			sldns_buffer_free(parsebuf);
			return 0;
		}
	}
	for(f = cfg->trust_anchor_list; f; f = f->next) {
		if(!f->str || f->str[0] == 0) /* empty "" */
			continue;
		if(!anchor_store_str(anchors, parsebuf, f->str)) {
			log_err("error in trust-anchor: \"%s\"", f->str);
			sldns_buffer_free(parsebuf);
			return 0;
		}
	}
	if(cfg->dlv_anchor_file && cfg->dlv_anchor_file[0] != 0) {
		struct trust_anchor* dlva;
		nm = cfg->dlv_anchor_file;
		if(cfg->chrootdir && cfg->chrootdir[0] && strncmp(nm,
			cfg->chrootdir, strlen(cfg->chrootdir)) == 0)
			nm += strlen(cfg->chrootdir);
		if(!(dlva = anchor_read_file(anchors, parsebuf,
			nm, 1))) {
			log_err("error reading dlv-anchor-file: %s", 
				cfg->dlv_anchor_file);
			sldns_buffer_free(parsebuf);
			return 0;
		}
		lock_basic_lock(&anchors->lock);
		anchors->dlv_anchor = dlva;
		lock_basic_unlock(&anchors->lock);
	}
	for(f = cfg->dlv_anchor_list; f; f = f->next) {
		struct trust_anchor* dlva;
		if(!f->str || f->str[0] == 0) /* empty "" */
			continue;
		if(!(dlva = anchor_store_str(
			anchors, parsebuf, f->str))) {
			log_err("error in dlv-anchor: \"%s\"", f->str);
			sldns_buffer_free(parsebuf);
			return 0;
		}
		lock_basic_lock(&anchors->lock);
		anchors->dlv_anchor = dlva;
		lock_basic_unlock(&anchors->lock);
	}
	/* do autr last, so that it sees what anchors are filled by other
	 * means can can print errors about double config for the name */
	for(f = cfg->auto_trust_anchor_file_list; f; f = f->next) {
		if(!f->str || f->str[0] == 0) /* empty "" */
			continue;
		nm = f->str;
		if(cfg->chrootdir && cfg->chrootdir[0] && strncmp(nm,
			cfg->chrootdir, strlen(cfg->chrootdir)) == 0)
			nm += strlen(cfg->chrootdir);
		if(!autr_read_file(anchors, nm)) {
			log_err("error reading auto-trust-anchor-file: %s", 
				f->str);
			sldns_buffer_free(parsebuf);
			return 0;
		}
	}
	/* first assemble, since it may delete useless anchors */
	anchors_assemble_rrsets(anchors);
	init_parents(anchors);
	sldns_buffer_free(parsebuf);
	if(verbosity >= VERB_ALGO) autr_debug_print(anchors);
	return 1;
}