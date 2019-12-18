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
struct manconf {int /*<<< orphan*/  manpath; } ;

/* Variables and functions */
 char* MAN_CONF_FILE ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  manconf_file (struct manconf*,char const*) ; 
 int /*<<< orphan*/  manpath_parseline (int /*<<< orphan*/ *,char*,char) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

void
manconf_parse(struct manconf *conf, const char *file,
		char *defp, char *auxp)
{
	char		*insert;

	/* Always prepend -m. */
	manpath_parseline(&conf->manpath, auxp, 'm');

	/* If -M is given, it overrides everything else. */
	if (NULL != defp) {
		manpath_parseline(&conf->manpath, defp, 'M');
		return;
	}

	/* MANPATH and man.conf(5) cooperate. */
	defp = getenv("MANPATH");
	if (NULL == file)
		file = MAN_CONF_FILE;

	/* No MANPATH; use man.conf(5) only. */
	if (NULL == defp || '\0' == defp[0]) {
		manconf_file(conf, file);
		return;
	}

	/* Prepend man.conf(5) to MANPATH. */
	if (':' == defp[0]) {
		manconf_file(conf, file);
		manpath_parseline(&conf->manpath, defp, '\0');
		return;
	}

	/* Append man.conf(5) to MANPATH. */
	if (':' == defp[strlen(defp) - 1]) {
		manpath_parseline(&conf->manpath, defp, '\0');
		manconf_file(conf, file);
		return;
	}

	/* Insert man.conf(5) into MANPATH. */
	insert = strstr(defp, "::");
	if (NULL != insert) {
		*insert++ = '\0';
		manpath_parseline(&conf->manpath, defp, '\0');
		manconf_file(conf, file);
		manpath_parseline(&conf->manpath, insert + 1, '\0');
		return;
	}

	/* MANPATH overrides man.conf(5) completely. */
	manpath_parseline(&conf->manpath, defp, '\0');
}