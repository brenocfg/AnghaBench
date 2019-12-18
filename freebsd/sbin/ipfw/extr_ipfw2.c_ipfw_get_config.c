#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct format_opts {int /*<<< orphan*/  last; int /*<<< orphan*/  first; int /*<<< orphan*/  flags; } ;
struct cmdline_opts {scalar_t__ test_only; } ;
struct TYPE_5__ {size_t size; int /*<<< orphan*/  opheader; int /*<<< orphan*/  end_rule; int /*<<< orphan*/  start_rule; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ipfw_cfg_lheader ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IP_FW_XGET ; 
 TYPE_1__* calloc (int,size_t) ; 
 scalar_t__ do_get3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
ipfw_get_config(struct cmdline_opts *co, struct format_opts *fo,
    ipfw_cfg_lheader **pcfg, size_t *psize)
{
	ipfw_cfg_lheader *cfg;
	size_t sz;
	int i;


	if (co->test_only != 0) {
		fprintf(stderr, "Testing only, list disabled\n");
		return (0);
	}

	/* Start with some data size */
	sz = 4096;
	cfg = NULL;

	for (i = 0; i < 16; i++) {
		if (cfg != NULL)
			free(cfg);
		if ((cfg = calloc(1, sz)) == NULL)
			return (ENOMEM);

		cfg->flags = fo->flags;
		cfg->start_rule = fo->first;
		cfg->end_rule = fo->last;

		if (do_get3(IP_FW_XGET, &cfg->opheader, &sz) != 0) {
			if (errno != ENOMEM) {
				free(cfg);
				return (errno);
			}

			/* Buffer size is not enough. Try to increase */
			sz = sz * 2;
			if (sz < cfg->size)
				sz = cfg->size;
			continue;
		}

		*pcfg = cfg;
		*psize = sz;
		return (0);
	}

	free(cfg);
	return (ENOMEM);
}