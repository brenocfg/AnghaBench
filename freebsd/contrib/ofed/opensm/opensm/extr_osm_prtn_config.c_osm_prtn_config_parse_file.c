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
struct part_conf {int dummy; } ;
typedef  int /*<<< orphan*/  osm_subn_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 int /*<<< orphan*/  OSM_LOG_VERBOSE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_part_conf (struct part_conf*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 struct part_conf* new_part_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int parse_part_conf (struct part_conf*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int osm_prtn_config_parse_file(osm_log_t * p_log, osm_subn_t * p_subn,
			       const char *file_name)
{
	char line[4096];
	struct part_conf *conf = NULL;
	FILE *file;
	int lineno;
	int is_parse_success;

	line[0] = '\0';
	file = fopen(file_name, "r");
	if (!file) {
		OSM_LOG(p_log, OSM_LOG_VERBOSE,
			"Cannot open config file \'%s\': %s\n",
			file_name, strerror(errno));
		return -1;
	}

	lineno = 0;

	is_parse_success = 0;

	while (fgets(line, sizeof(line) - 1, file) != NULL) {
		char *q, *p = line;

		lineno++;

		p = line;

		q = strchr(p, '#');
		if (q)
			*q = '\0';

		do {
			int len;
			while (*p == ' ' || *p == '\t' || *p == '\n')
				p++;
			if (*p == '\0')
				break;

			if (!conf && !(conf = new_part_conf(p_log, p_subn))) {
				OSM_LOG(p_log, OSM_LOG_ERROR,
					"PARSE ERROR: line %d: "
					"internal: cannot create config\n",
					lineno);
				fprintf(stderr,
					"PARSE ERROR: line %d: "
					"internal: cannot create config\n",
					lineno);
				is_parse_success = -1;
				break;
			}

			q = strchr(p, ';');
			if (q)
				*q = '\0';

			len = parse_part_conf(conf, p, lineno);
			if (len < 0) {
				is_parse_success = -1;
				break;
			}

			is_parse_success = 1;

			p += len;

			if (q) {
				flush_part_conf(conf);
				conf = NULL;
			}
		} while (q);

		if (is_parse_success == -1)
			break;
	}

	fclose(file);

	return (is_parse_success == 1) ? 0 : 1;
}