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
struct passwd {char* pw_dir; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int PATH_MAX ; 
 int SSHCONF_CHECKPERM ; 
 int SSHCONF_POSTCANON ; 
 int SSHCONF_USERCONF ; 
 char* _PATH_HOST_CONFIG_FILE ; 
 char* _PATH_SSH_USER_CONFFILE ; 
 char* config ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  read_config_file (char*,struct passwd*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int) ; 
 int snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_config_files(const char *host_name, struct passwd *pw, int post_canon)
{
	char buf[PATH_MAX];
	int r;

	if (config != NULL) {
		if (strcasecmp(config, "none") != 0 &&
		    !read_config_file(config, pw, host, host_name, &options,
		    SSHCONF_USERCONF | (post_canon ? SSHCONF_POSTCANON : 0)))
			fatal("Can't open user config file %.100s: "
			    "%.100s", config, strerror(errno));
	} else {
		r = snprintf(buf, sizeof buf, "%s/%s", pw->pw_dir,
		    _PATH_SSH_USER_CONFFILE);
		if (r > 0 && (size_t)r < sizeof(buf))
			(void)read_config_file(buf, pw, host, host_name,
			    &options, SSHCONF_CHECKPERM | SSHCONF_USERCONF |
			    (post_canon ? SSHCONF_POSTCANON : 0));

		/* Read systemwide configuration file after user config. */
		(void)read_config_file(_PATH_HOST_CONFIG_FILE, pw,
		    host, host_name, &options,
		    post_canon ? SSHCONF_POSTCANON : 0);
	}
}