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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  IBND_CONFIG_MLX_EPI ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* ibd_ca ; 
 void* ibd_ca_port ; 
 int /*<<< orphan*/  ibd_ibnetdisc_flags ; 
 void* ibd_mkey ; 
 void* ibd_nd_format ; 
 void* ibd_sakey ; 
 void* ibd_timeout ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 char* strtok_r (char*,char*,char**) ; 
 void* strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* strtoull (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ val_str_true (char*) ; 

void read_ibdiag_config(const char *file)
{
	char buf[1024];
	FILE *config_fd = NULL;
	char *p_prefix, *p_last;
	char *name;
	char *val_str;
	struct stat statbuf;

	/* silently ignore missing config file */
	if (stat(file, &statbuf))
		return;

	config_fd = fopen(file, "r");
	if (!config_fd)
		return;

	while (fgets(buf, sizeof buf, config_fd) != NULL) {
		p_prefix = strtok_r(buf, "\n", &p_last);
		if (!p_prefix)
			continue; /* ignore blank lines */

		if (*p_prefix == '#')
			continue; /* ignore comment lines */

		name = strtok_r(p_prefix, "=", &p_last);
		val_str = strtok_r(NULL, "\n", &p_last);

		if (strncmp(name, "CA", strlen("CA")) == 0) {
			free(ibd_ca);
			ibd_ca = strdup(val_str);
		} else if (strncmp(name, "Port", strlen("Port")) == 0) {
			ibd_ca_port = strtoul(val_str, NULL, 0);
		} else if (strncmp(name, "timeout", strlen("timeout")) == 0) {
			ibd_timeout = strtoul(val_str, NULL, 0);
		} else if (strncmp(name, "MLX_EPI", strlen("MLX_EPI")) == 0) {
			if (val_str_true(val_str)) {
				ibd_ibnetdisc_flags |= IBND_CONFIG_MLX_EPI;
			} else {
				ibd_ibnetdisc_flags &= ~IBND_CONFIG_MLX_EPI;
			}
		} else if (strncmp(name, "m_key", strlen("m_key")) == 0) {
			ibd_mkey = strtoull(val_str, 0, 0);
		} else if (strncmp(name, "sa_key",
				   strlen("sa_key")) == 0) {
			ibd_sakey = strtoull(val_str, 0, 0);
		} else if (strncmp(name, "nd_format",
				   strlen("nd_format")) == 0) {
			ibd_nd_format = strdup(val_str);
		}
	}

	fclose(config_fd);
}