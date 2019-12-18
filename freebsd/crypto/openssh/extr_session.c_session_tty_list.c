#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ttyfd; char* tty; scalar_t__ used; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 TYPE_1__* sessions ; 
 int sessions_nalloc ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char *
session_tty_list(void)
{
	static char buf[1024];
	int i;
	char *cp;

	buf[0] = '\0';
	for (i = 0; i < sessions_nalloc; i++) {
		Session *s = &sessions[i];
		if (s->used && s->ttyfd != -1) {

			if (strncmp(s->tty, "/dev/", 5) != 0) {
				cp = strrchr(s->tty, '/');
				cp = (cp == NULL) ? s->tty : cp + 1;
			} else
				cp = s->tty + 5;

			if (buf[0] != '\0')
				strlcat(buf, ",", sizeof buf);
			strlcat(buf, cp, sizeof buf);
		}
	}
	if (buf[0] == '\0')
		strlcpy(buf, "notty", sizeof buf);
	return buf;
}