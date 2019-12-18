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
struct stat {int dummy; } ;

/* Variables and functions */
 scalar_t__ SWAPON ; 
 int /*<<< orphan*/  _PATH_GELI ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ qflag ; 
 int run_cmd (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char*) ; 
 int stat (char const*,struct stat*) ; 
 char* swap_basename (char const*) ; 
 char* swap_on_geli_args (char*) ; 
 char const* swap_on_off_sfile (char const*,int) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 
 scalar_t__ which_prog ; 

__attribute__((used)) static const char *
swap_on_off_geli(const char *name, char *mntops, int doingall)
{
	struct stat sb;
	char *dname, *args;
	int error;

	error = stat(name, &sb);

	if (which_prog == SWAPON) do {
		/* Skip if the .eli device already exists. */
		if (error == 0)
			break;

		args = swap_on_geli_args(mntops);
		if (args == NULL)
			return (NULL);

		dname = swap_basename(name);
		if (dname == NULL) {
			free(args);
			return (NULL);
		}

		error = run_cmd(NULL, "%s onetime%s %s", _PATH_GELI, args,
		    dname);

		free(dname);
		free(args);

		if (error) {
			/* error occurred during creation. */
			if (qflag == 0)
				warnx("%s: Invalid parameters", name);
			return (NULL);
		}
	} while (0);

	return (swap_on_off_sfile(name, doingall));
}