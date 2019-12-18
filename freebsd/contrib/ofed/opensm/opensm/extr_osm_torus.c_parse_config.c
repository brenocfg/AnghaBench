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
struct torus {unsigned int* port_order; int flags; TYPE_1__* osm; int /*<<< orphan*/  max_changes; int /*<<< orphan*/  seed_cnt; int /*<<< orphan*/  portgrp_sz; } ;
struct fabric {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  log; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  DEFAULT_MAX_CHANGES ; 
 int NOTIFY_CHANGES ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  PORTGRP_MAX_PORTS ; 
 int X_MESH ; 
 int Y_MESH ; 
 int Z_MESH ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int grow_seed_array (struct torus*,int) ; 
 int parse_dir_dateline (int,struct torus*,char const*) ; 
 int parse_dir_link (int,struct torus*,char const*) ; 
 int parse_port_order (struct torus*,char const*) ; 
 int parse_torus (struct torus*,char const*) ; 
 int parse_unsigned (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 unsigned int strerror (int /*<<< orphan*/ ) ; 
 char* strtok (char*,char const*) ; 

__attribute__((used)) static
bool parse_config(const char *fn, struct fabric *f, struct torus *t)
{
	FILE *fp;
	unsigned i;
	char *keyword;
	char *line_buf = NULL;
	const char *parse_sep = " \n\t\015";
	size_t line_buf_sz = 0;
	size_t line_cntr = 0;
	ssize_t llen;
	bool kw_success, success = true;

	if (!grow_seed_array(t, 2))
		return false;

	for (i = 0; i < ARRAY_SIZE(t->port_order); i++)
		t->port_order[i] = i;

	fp = fopen(fn, "r");
	if (!fp) {
		OSM_LOG(&t->osm->log, OSM_LOG_ERROR,
			"ERR 4E11: Opening %s: %s\n", fn, strerror(errno));
		return false;
	}
	t->flags |= NOTIFY_CHANGES;
	t->portgrp_sz = PORTGRP_MAX_PORTS;
	t->max_changes = DEFAULT_MAX_CHANGES;

next_line:
	llen = getline(&line_buf, &line_buf_sz, fp);
	if (llen < 0)
		goto out;

	++line_cntr;

	keyword = strtok(line_buf, parse_sep);
	if (!keyword)
		goto next_line;

	if (strcmp("torus", keyword) == 0) {
		kw_success = parse_torus(t, parse_sep);
	} else if (strcmp("mesh", keyword) == 0) {
		t->flags |= X_MESH | Y_MESH | Z_MESH;
		kw_success = parse_torus(t, parse_sep);
	} else if (strcmp("port_order", keyword) == 0) {
		kw_success = parse_port_order(t, parse_sep);
	} else if (strcmp("next_seed", keyword) == 0) {
		kw_success = grow_seed_array(t, 1);
		t->seed_cnt++;
	} else if (strcmp("portgroup_max_ports", keyword) == 0) {
		kw_success = parse_unsigned(&t->portgrp_sz, parse_sep);
	} else if (strcmp("xp_link", keyword) == 0) {
		if (!t->seed_cnt)
			t->seed_cnt++;
		kw_success = parse_dir_link(1, t, parse_sep);
	} else if (strcmp("xm_link", keyword) == 0) {
		if (!t->seed_cnt)
			t->seed_cnt++;
		kw_success = parse_dir_link(-1, t, parse_sep);
	} else if (strcmp("x_dateline", keyword) == 0) {
		if (!t->seed_cnt)
			t->seed_cnt++;
		kw_success = parse_dir_dateline(1, t, parse_sep);
	} else if (strcmp("yp_link", keyword) == 0) {
		if (!t->seed_cnt)
			t->seed_cnt++;
		kw_success = parse_dir_link(2, t, parse_sep);
	} else if (strcmp("ym_link", keyword) == 0) {
		if (!t->seed_cnt)
			t->seed_cnt++;
		kw_success = parse_dir_link(-2, t, parse_sep);
	} else if (strcmp("y_dateline", keyword) == 0) {
		if (!t->seed_cnt)
			t->seed_cnt++;
		kw_success = parse_dir_dateline(2, t, parse_sep);
	} else if (strcmp("zp_link", keyword) == 0) {
		if (!t->seed_cnt)
			t->seed_cnt++;
		kw_success = parse_dir_link(3, t, parse_sep);
	} else if (strcmp("zm_link", keyword) == 0) {
		if (!t->seed_cnt)
			t->seed_cnt++;
		kw_success = parse_dir_link(-3, t, parse_sep);
	} else if (strcmp("z_dateline", keyword) == 0) {
		if (!t->seed_cnt)
			t->seed_cnt++;
		kw_success = parse_dir_dateline(3, t, parse_sep);
	} else if (strcmp("max_changes", keyword) == 0) {
		kw_success = parse_unsigned(&t->max_changes, parse_sep);
	} else if (keyword[0] == '#')
		goto next_line;
	else {
		OSM_LOG(&t->osm->log, OSM_LOG_ERROR,
			"ERR 4E12: no keyword found: line %u\n",
			(unsigned)line_cntr);
		kw_success = false;
	}
	if (!kw_success) {
		OSM_LOG(&t->osm->log, OSM_LOG_ERROR,
			"ERR 4E13: parsing '%s': line %u\n",
			keyword, (unsigned)line_cntr);
	}
	success = success && kw_success;
	goto next_line;

out:
	if (line_buf)
		free(line_buf);
	fclose(fp);
	return success;
}