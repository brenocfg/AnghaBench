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
typedef  int /*<<< orphan*/  pass ;
typedef  int /*<<< orphan*/  bpass ;

/* Variables and functions */
 scalar_t__ SWAPOFF ; 
 scalar_t__ SWAPON ; 
 int /*<<< orphan*/  _PATH_GBDE ; 
 int /*<<< orphan*/  arc4random_buf (unsigned char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ qflag ; 
 int run_cmd (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 
 char* swap_basename (char const*) ; 
 char* swap_on_off_sfile (char const*,int) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 
 scalar_t__ which_prog ; 

__attribute__((used)) static const char *
swap_on_off_gbde(const char *name, int doingall)
{
	const char *ret;
	char pass[64 * 2 + 1];
	unsigned char bpass[64];
	char *dname;
	int i, error;

	dname = swap_basename(name);
	if (dname == NULL)
		return (NULL);

	if (which_prog == SWAPON) {
		arc4random_buf(bpass, sizeof(bpass));
		for (i = 0; i < (int)sizeof(bpass); i++)
			sprintf(&pass[2 * i], "%02x", bpass[i]);
		pass[sizeof(pass) - 1] = '\0';

		error = run_cmd(NULL, "%s init %s -P %s", _PATH_GBDE,
		    dname, pass);
		if (error) {
			/* bde device found.  Ignore it. */
			free(dname);
			if (qflag == 0)
				warnx("%s: Device already in use", name);
			return (NULL);
		}
		error = run_cmd(NULL, "%s attach %s -p %s", _PATH_GBDE,
		    dname, pass);
		free(dname);
		if (error) {
			warnx("gbde (attach) error: %s", name);
			return (NULL);
		}
	}

	ret = swap_on_off_sfile(name, doingall);

	if (which_prog == SWAPOFF) {
		error = run_cmd(NULL, "%s detach %s", _PATH_GBDE, dname);
		free(dname);
		if (error) {
			/* bde device not found.  Ignore it. */
			if (qflag == 0)
				warnx("%s: Device not found", name);
			return (NULL);
		}
	}

	return (ret);
}