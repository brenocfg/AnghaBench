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
struct mt_status_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int mt_param_list (struct mt_status_data*,char*,int) ; 
 int mt_set_param (int,struct mt_status_data*,char*,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
mt_param(int argc, char **argv, int mtfd, char *xml_str,
	 struct mt_status_data *status_data)
{
	int list = 0, do_set = 0, xml_dump = 0;
	char *param_name = NULL, *param_value = NULL;
	int retval = 0, quiet = 0;
	int c;

	while ((c = getopt(argc, argv, "lp:qs:x")) != -1) {
		switch (c) {
		case 'l':
			list = 1;
			break;
		case 'p':
			if (param_name != NULL) {
				warnx("Only one parameter name may be "
				    "specified");
				retval = 1;
				goto bailout;
			}
			param_name = strdup(optarg);
			break;
		case 'q':
			quiet = 1;
			break;
		case 's':
			if (param_value != NULL) {
				warnx("Only one parameter value may be "
				    "specified");
				retval = 1;
				goto bailout;
			}
			param_value = strdup(optarg);
			do_set = 1;
			break;
		case 'x':
			xml_dump = 1;
			break;
		default:
			break;
		}
	}

	if ((list + do_set + xml_dump) != 1) {
		warnx("You must specify only one of -s, -l or -x");
		retval = 1;
		goto bailout;
	}

	if (xml_dump != 0) {
		printf("%s", xml_str);
		retval = 0;
		goto bailout;
	}

	if (do_set != 0) {
		if (param_name == NULL)
			errx(1, "You must specify -p with -s");

		retval = mt_set_param(mtfd, status_data, param_name,
		    param_value);
	} else if (list != 0)
		retval = mt_param_list(status_data, param_name, quiet);

bailout:
	free(param_name);
	free(param_value);
	return (retval);
}