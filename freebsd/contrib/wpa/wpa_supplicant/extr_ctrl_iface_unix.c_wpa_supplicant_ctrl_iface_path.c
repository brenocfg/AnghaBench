#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {char* ifname; TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ctrl_interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 int os_snprintf (char*,size_t,char*,char*,char*) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 
 char* os_strdup (int /*<<< orphan*/ *) ; 
 int os_strlen (char*) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 char* os_strstr (char*,char*) ; 

__attribute__((used)) static char * wpa_supplicant_ctrl_iface_path(struct wpa_supplicant *wpa_s)
{
	char *buf;
	size_t len;
	char *pbuf, *dir = NULL;
	int res;

	if (wpa_s->conf->ctrl_interface == NULL)
		return NULL;

	pbuf = os_strdup(wpa_s->conf->ctrl_interface);
	if (pbuf == NULL)
		return NULL;
	if (os_strncmp(pbuf, "DIR=", 4) == 0) {
		char *gid_str;
		dir = pbuf + 4;
		gid_str = os_strstr(dir, " GROUP=");
		if (gid_str)
			*gid_str = '\0';
	} else
		dir = pbuf;

	len = os_strlen(dir) + os_strlen(wpa_s->ifname) + 2;
	buf = os_malloc(len);
	if (buf == NULL) {
		os_free(pbuf);
		return NULL;
	}

	res = os_snprintf(buf, len, "%s/%s", dir, wpa_s->ifname);
	if (os_snprintf_error(len, res)) {
		os_free(pbuf);
		os_free(buf);
		return NULL;
	}
#ifdef __CYGWIN__
	{
		/* Windows/WinPcap uses interface names that are not suitable
		 * as a file name - convert invalid chars to underscores */
		char *pos = buf;
		while (*pos) {
			if (*pos == '\\')
				*pos = '_';
			pos++;
		}
	}
#endif /* __CYGWIN__ */
	os_free(pbuf);
	return buf;
}