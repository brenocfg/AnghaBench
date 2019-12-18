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
struct fibl_head_t {int dummy; } ;
struct fibl {int fl_num; } ;

/* Variables and functions */
 int ALLSTRLEN ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct fibl_head_t*,struct fibl*,int /*<<< orphan*/ ) ; 
 void* calloc (int,int) ; 
 int defaultfib ; 
 scalar_t__ errno ; 
 int fiboptlist_range (char*,struct fibl_head_t*) ; 
 int /*<<< orphan*/  fl_next ; 
 int /*<<< orphan*/  free (char*) ; 
 int numfibs ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fiboptlist_csv(const char *arg, struct fibl_head_t *flh)
{
	struct fibl *fl;
	char *str0, *str, *token, *endptr;
	int fib, error;

	str0 = str = NULL;
	if (strcmp("all", arg) == 0) {
		str = calloc(1, ALLSTRLEN);
		if (str == NULL) {
			error = 1;
			goto fiboptlist_csv_ret;
		}
		if (numfibs > 1)
			snprintf(str, ALLSTRLEN - 1, "%d-%d", 0, numfibs - 1);
		else
			snprintf(str, ALLSTRLEN - 1, "%d", 0);
	} else if (strcmp("default", arg) == 0) {
		str0 = str = calloc(1, ALLSTRLEN);
		if (str == NULL) {
			error = 1;
			goto fiboptlist_csv_ret;
		}
		snprintf(str, ALLSTRLEN - 1, "%d", defaultfib);
	} else
		str0 = str = strdup(arg);

	error = 0;
	while ((token = strsep(&str, ",")) != NULL) {
		if (*token != '-' && strchr(token, '-') != NULL) {
			error = fiboptlist_range(token, flh);
			if (error)
				goto fiboptlist_csv_ret;
		} else {
			errno = 0;
			fib = strtol(token, &endptr, 0);
			if (errno == 0) {
				if (*endptr != '\0' ||
				    fib < 0 ||
				    (numfibs != -1 && fib > numfibs - 1))
					errno = EINVAL;
			}
			if (errno) {
				error = 1;
				goto fiboptlist_csv_ret;
			}
			fl = calloc(1, sizeof(*fl));
			if (fl == NULL) {
				error = 1;
				goto fiboptlist_csv_ret;
			}
			fl->fl_num = fib;
			TAILQ_INSERT_TAIL(flh, fl, fl_next);
		}
	}
fiboptlist_csv_ret:
	if (str0 != NULL)
		free(str0);
	return (error);
}