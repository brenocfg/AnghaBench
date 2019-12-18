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
struct keymap {char* keym; } ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dir ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_extension (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* strdup (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  vidcontrol (char*) ; 

__attribute__((used)) static void
do_vidfont(struct keymap *km)
{
	char *vid_cmd, *tmp, *p, *q;

	asprintf(&vid_cmd, "%s/%s", dir, km->keym);
	vidcontrol(vid_cmd);
	free(vid_cmd);

	tmp = strdup(km->keym);
	p = strrchr(tmp, '-');
	if (p && p[1]!='\0') {
		p++;
		q = get_extension(p);
		if (q) {
			*q = '\0';
			printf("font%s=%s\n", p, km->keym);
		}
	}
	free(tmp);
}