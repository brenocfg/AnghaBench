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
struct configuration {int dummy; } ;
typedef  int /*<<< orphan*/  fields ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR_2 (char*,char*,char const*,int) ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct configuration*,char const*,char const**,int*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct configuration*,char const*,char const**,int*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_cachename (char*) ; 
 int /*<<< orphan*/  check_files (struct configuration*,char*,int) ; 
 int /*<<< orphan*/  enable_cache (struct configuration*,char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int get_number (char*,int,int) ; 
 int get_policy (char*) ; 
 int get_yesno (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_keep_hot_count (struct configuration*,char*,int) ; 
 int /*<<< orphan*/  set_negative_confidence_threshold (struct configuration*,char*,int) ; 
 int /*<<< orphan*/  set_negative_policy (struct configuration*,char*,int) ; 
 int /*<<< orphan*/  set_negative_time_to_live (struct configuration*,char*,int) ; 
 int /*<<< orphan*/  set_perform_actual_lookups (struct configuration*,char*,int) ; 
 int /*<<< orphan*/  set_positive_confidence_threshold (struct configuration*,char*,int) ; 
 int /*<<< orphan*/  set_positive_policy (struct configuration*,char*,int) ; 
 int /*<<< orphan*/  set_positive_time_to_live (struct configuration*,char*,int) ; 
 int /*<<< orphan*/  set_suggested_size (struct configuration*,char*,int) ; 
 int /*<<< orphan*/  set_threads_num (struct configuration*,int) ; 
 int strbreak (char*,char**,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int
parse_config_file(struct configuration *config,
	const char *fname, char const **error_str, int *error_line)
{
	FILE	*fin;
	char	buffer[255];
	char	*fields[128];
	int	field_count, line_num, value;
	int	res;

	TRACE_IN(parse_config_file);
	assert(config != NULL);
	assert(fname != NULL);

	fin = fopen(fname, "r");
	if (fin == NULL) {
		TRACE_OUT(parse_config_file);
		return (-1);
	}

	res = 0;
	line_num = 0;
	memset(buffer, 0, sizeof(buffer));
	while ((res == 0) && (fgets(buffer, sizeof(buffer) - 1, fin) != NULL)) {
		field_count = strbreak(buffer, fields, sizeof(fields));
		++line_num;

		if (field_count == 0)
			continue;

		switch (fields[0][0]) {
		case '#':
		case '\0':
			continue;
		case 'e':
			if ((field_count == 3) &&
			(strcmp(fields[0], "enable-cache") == 0) &&
			(check_cachename(fields[1]) == 0) &&
			((value = get_yesno(fields[2])) != -1)) {
				enable_cache(config, fields[1], value);
				continue;
			}
			break;
		case 'd':
			if ((field_count == 2) &&
			(strcmp(fields[0], "debug-level") == 0) &&
			((value = get_number(fields[1], 0, 10)) != -1)) {
				continue;
			}
			break;
		case 'p':
			if ((field_count == 3) &&
			(strcmp(fields[0], "positive-time-to-live") == 0) &&
			(check_cachename(fields[1]) == 0) &&
			((value = get_number(fields[2], 0, -1)) != -1)) {
				set_positive_time_to_live(config,
					fields[1], value);
				continue;
			} else if ((field_count == 3) &&
			(strcmp(fields[0], "positive-confidence-threshold") == 0) &&
			((value = get_number(fields[2], 1, -1)) != -1)) {
				set_positive_confidence_threshold(config,
					fields[1], value);
				continue;
			} else if ((field_count == 3) &&
			(strcmp(fields[0], "positive-policy") == 0) &&
			(check_cachename(fields[1]) == 0) &&
			((value = get_policy(fields[2])) != -1)) {
				set_positive_policy(config, fields[1], value);
				continue;
			} else if ((field_count == 3) &&
			(strcmp(fields[0], "perform-actual-lookups") == 0) &&
			(check_cachename(fields[1]) == 0) &&
			((value = get_yesno(fields[2])) != -1)) {
				set_perform_actual_lookups(config, fields[1],
					value);
				continue;
			}
			break;
		case 'n':
			if ((field_count == 3) &&
			(strcmp(fields[0], "negative-time-to-live") == 0) &&
			(check_cachename(fields[1]) == 0) &&
			((value = get_number(fields[2], 0, -1)) != -1)) {
				set_negative_time_to_live(config,
					fields[1], value);
				continue;
			} else if ((field_count == 3) &&
			(strcmp(fields[0], "negative-confidence-threshold") == 0) &&
			((value = get_number(fields[2], 1, -1)) != -1)) {
				set_negative_confidence_threshold(config,
					fields[1], value);
				continue;
			} else if ((field_count == 3) &&
			(strcmp(fields[0], "negative-policy") == 0) &&
			(check_cachename(fields[1]) == 0) &&
			((value = get_policy(fields[2])) != -1)) {
				set_negative_policy(config,
					fields[1], value);
				continue;
			}
			break;
		case 's':
			if ((field_count == 3) &&
			(strcmp(fields[0], "suggested-size") == 0) &&
			(check_cachename(fields[1]) == 0) &&
			((value = get_number(fields[2], 1, -1)) != -1)) {
				set_suggested_size(config, fields[1], value);
				continue;
			}
			break;
		case 't':
			if ((field_count == 2) &&
			(strcmp(fields[0], "threads") == 0) &&
			((value = get_number(fields[1], 1, -1)) != -1)) {
				set_threads_num(config, value);
				continue;
			}
			break;
		case 'k':
			if ((field_count == 3) &&
			(strcmp(fields[0], "keep-hot-count") == 0) &&
			(check_cachename(fields[1]) == 0) &&
			((value = get_number(fields[2], 0, -1)) != -1)) {
				set_keep_hot_count(config,
					fields[1], value);
				continue;
			}
			break;
		case 'c':
			if ((field_count == 3) &&
			(strcmp(fields[0], "check-files") == 0) &&
			(check_cachename(fields[1]) == 0) &&
			((value = get_yesno(fields[2])) != -1)) {
				check_files(config,
					fields[1], value);
				continue;
			}
			break;
		default:
			break;
		}

		LOG_ERR_2("config file parser", "error in file "
			"%s on line %d", fname, line_num);
		*error_str = "syntax error";
		*error_line = line_num;
		res = -1;
	}
	fclose(fin);

	TRACE_OUT(parse_config_file);
	return (res);
}