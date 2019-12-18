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
typedef  int /*<<< orphan*/  uint8_t ;
struct name_tree_node {int dummy; } ;
struct iter_priv {int /*<<< orphan*/  n; int /*<<< orphan*/  region; } ;
struct config_strlist {int /*<<< orphan*/  str; struct config_strlist* next; } ;
struct config_file {struct config_strlist* private_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int dname_count_size_labels (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  name_tree_insert (int /*<<< orphan*/ *,struct name_tree_node*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 scalar_t__ regional_alloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ regional_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * sldns_str2wire_dname (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_names(struct iter_priv* priv, struct config_file* cfg)
{
	/* parse names, report errors, insert into tree */
	struct config_strlist* p;
	struct name_tree_node* n;
	uint8_t* nm, *nmr;
	size_t nm_len;
	int nm_labs;

	for(p = cfg->private_domain; p; p = p->next) {
		log_assert(p->str);
		nm = sldns_str2wire_dname(p->str, &nm_len);
		if(!nm) {
			log_err("cannot parse private-domain: %s", p->str);
			return 0;
		}
		nm_labs = dname_count_size_labels(nm, &nm_len);
		nmr = (uint8_t*)regional_alloc_init(priv->region, nm, nm_len);
		free(nm);
		if(!nmr) {
			log_err("out of memory");
			return 0;
		}
		n = (struct name_tree_node*)regional_alloc(priv->region,
			sizeof(*n));
		if(!n) {
			log_err("out of memory");
			return 0;
		}
		if(!name_tree_insert(&priv->n, n, nmr, nm_len, nm_labs,
			LDNS_RR_CLASS_IN)) {
			verbose(VERB_QUERY, "ignoring duplicate "
				"private-domain: %s", p->str);
		}
	}
	return 1;
}