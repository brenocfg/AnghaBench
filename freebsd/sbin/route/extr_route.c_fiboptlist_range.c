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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct fibl_head_t*,struct fibl*,int /*<<< orphan*/ ) ; 
 struct fibl* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fl_next ; 
 int /*<<< orphan*/  free (char*) ; 
 int numfibs ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fiboptlist_range(const char *arg, struct fibl_head_t *flh)
{
	struct fibl *fl;
	char *str0, *str, *token, *endptr;
	int fib[2], i, error;

	str0 = str = strdup(arg);
	error = 0;
	i = 0;
	while ((token = strsep(&str, "-")) != NULL) {
		switch (i) {
		case 0:
		case 1:
			errno = 0;
			fib[i] = strtol(token, &endptr, 0);
			if (errno == 0) {
				if (*endptr != '\0' ||
				    fib[i] < 0 ||
				    (numfibs != -1 && fib[i] > numfibs - 1))
					errno = EINVAL;
			}
			if (errno)
				error = 1;
			break;
		default:
			error = 1;
		}
		if (error)
			goto fiboptlist_range_ret;
		i++;
	}
	if (fib[0] >= fib[1]) {
		error = 1;
		goto fiboptlist_range_ret;
	}
	for (i = fib[0]; i <= fib[1]; i++) {
		fl = calloc(1, sizeof(*fl));
		if (fl == NULL) {
			error = 1;
			goto fiboptlist_range_ret;
		}
		fl->fl_num = i;
		TAILQ_INSERT_TAIL(flh, fl, fl_next);
	}
fiboptlist_range_ret:
	free(str0);
	return (error);
}