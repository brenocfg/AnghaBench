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
struct wpa_ctrl {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 
 int /*<<< orphan*/  wpa_ctrl_close (struct wpa_ctrl*) ; 
 scalar_t__ wpa_ctrl_request (struct wpa_ctrl*,char*,int,char*,size_t*,int /*<<< orphan*/ *) ; 
 struct wpa_ctrl* wpa_open_ctrl (char const*) ; 

int get_wpa_status(const char *ifname, const char *field, char *obuf,
		   size_t obuf_size)
{
	struct wpa_ctrl *ctrl;
	char buf[4096];
	char *pos, *end;
	size_t len, flen;

	ctrl = wpa_open_ctrl(ifname);
	if (ctrl == NULL)
		return -1;
	len = sizeof(buf);
	if (wpa_ctrl_request(ctrl, "STATUS-NO_EVENTS", 16, buf, &len,
			     NULL) < 0) {
		wpa_ctrl_close(ctrl);
		return -1;
	}
	wpa_ctrl_close(ctrl);
	buf[len] = '\0';

	flen = strlen(field);
	pos = buf;
	while (pos + flen < buf + len) {
		if (pos > buf) {
			if (*pos != '\n') {
				pos++;
				continue;
			}
			pos++;
		}
		if (strncmp(pos, field, flen) != 0 || pos[flen] != '=') {
			pos++;
			continue;
		}
		pos += flen + 1;
		end = strchr(pos, '\n');
		if (end == NULL)
			return -1;
		*end++ = '\0';
		if (end - pos > (int) obuf_size)
			return -1;
		memcpy(obuf, pos, end - pos);
		return 0;
	}

	return -1;
}