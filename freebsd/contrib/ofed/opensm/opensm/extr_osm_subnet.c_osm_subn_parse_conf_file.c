#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char const* config_file; TYPE_6__* file_opts; } ;
typedef  TYPE_1__ osm_subn_opt_t ;
struct TYPE_10__ {int opt_offset; int /*<<< orphan*/  (* parse_fn ) (int /*<<< orphan*/ *,char*,char*,void*,void*,int /*<<< orphan*/ *) ;scalar_t__ name; } ;
typedef  TYPE_2__ opt_rec_t ;
struct TYPE_11__ {int /*<<< orphan*/ * file_opts; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 char* clean_val (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  log_report (char*,char*) ; 
 TYPE_6__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,TYPE_1__*,int) ; 
 TYPE_2__* opt_tbl ; 
 int /*<<< orphan*/  osm_subn_verify_config (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 char* strerror (scalar_t__) ; 
 char* strtok_r (char*,char*,char**) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*,char*,void*,void*,int /*<<< orphan*/ *) ; 

int osm_subn_parse_conf_file(const char *file_name, osm_subn_opt_t * p_opts)
{
	char line[1024];
	FILE *opts_file;
	char *p_key, *p_val, *pound_sign;
	const opt_rec_t *r;
	void *p_field1, *p_field2;
	int token_matched;

	opts_file = fopen(file_name, "r");
	if (!opts_file) {
		if (errno == ENOENT)
			return 1;
		printf("cannot open file \'%s\': %s\n",
		       file_name, strerror(errno));
		return -1;
	}

	printf(" Reading Cached Option File: %s\n", file_name);

	p_opts->config_file = file_name;
	if (!p_opts->file_opts && !(p_opts->file_opts = malloc(sizeof(*p_opts)))) {
		fclose(opts_file);
		return -1;
	}
	memcpy(p_opts->file_opts, p_opts, sizeof(*p_opts));
	p_opts->file_opts->file_opts = NULL;

	while (fgets(line, 1023, opts_file) != NULL) {
		pound_sign = strchr(line,'#');
		token_matched = 0;
		/* Truncate any comments. */
		if (pound_sign)
			*pound_sign = '\0';

		/* get the first token */
		p_key = strtok_r(line, " \t\n", &p_val);
		if (!p_key)
			continue;

		p_val = clean_val(p_val);

		for (r = opt_tbl; r->name; r++) {
			if (strcmp(r->name, p_key))
				continue;

			token_matched = 1;
			p_field1 = (void *)p_opts->file_opts + r->opt_offset;
			p_field2 = (void *)p_opts + r->opt_offset;
			/* don't call setup function first time */
			r->parse_fn(NULL, p_key, p_val, p_field1, p_field2,
				    NULL);
			break;
		}

		if (!token_matched)
			log_report(" Unrecognized token: \"%s\"\n", p_key);
	}
	fclose(opts_file);

	osm_subn_verify_config(p_opts);

	return 0;
}