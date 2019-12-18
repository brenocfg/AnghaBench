#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* str; int /*<<< orphan*/  boolean; } ;
struct TYPE_4__ {TYPE_1__ value; } ;

/* Variables and functions */
 char* DIALOGRC ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENV_DIALOGRC ; 
 int /*<<< orphan*/  ENV_HOME ; 
 int /*<<< orphan*/  FIGPAR_BREAK_ON_EQUALS ; 
 int PATH_MAX ; 
 int STR_BUFSIZE ; 
 int /*<<< orphan*/  dialogrc_config ; 
 TYPE_2__* dialogrc_config_option (char*) ; 
 int /*<<< orphan*/  errno ; 
 char* gauge_color ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int parse_config (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  use_colors ; 
 int /*<<< orphan*/  use_shadow ; 

int
parse_dialogrc(void)
{
	char *cp;
	int res;
	size_t len;
	char path[PATH_MAX];

	/* Allow $DIALOGRC to override `$HOME/.dialogrc' default */
	if ((cp = getenv(ENV_DIALOGRC)) != NULL && *cp != '\0')
		snprintf(path, PATH_MAX, "%s", cp);
	else if ((cp = getenv(ENV_HOME)) != NULL) {
		/* Copy $HOME into buffer and append trailing `/' if missing */
		snprintf(path, PATH_MAX, "%s", cp);
		len = strlen(path);
		cp = path + len;
		if (len > 0 && len < (PATH_MAX - 1) && *(cp - 1) != '/') {
			*cp++ = '/';
			*cp = '\0';
			len++;
		}

		/* If we still have room, shove in the name of rc file */
		if (len < (PATH_MAX - 1))
			snprintf(cp, PATH_MAX - len, "%s", DIALOGRC);
	} else {
		/* Like dialog(1), don't process a file if $HOME is unset */
		errno = ENOENT;
		return (-1);
	}

	/* Process file (either $DIALOGRC if set, or `$HOME/.dialogrc') */
	res = parse_config(dialogrc_config,
		path, NULL, FIGPAR_BREAK_ON_EQUALS);

	/* Set some globals based on what we parsed */
	use_shadow = dialogrc_config_option("use_shadow")->value.boolean;
	use_colors = dialogrc_config_option("use_colors")->value.boolean;
	snprintf(gauge_color, STR_BUFSIZE, "%s",
	    dialogrc_config_option("gauge_color")->value.str);

	return (res);
}