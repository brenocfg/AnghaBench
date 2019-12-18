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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 char* expand_user_path (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 char* xdg_cache_home (char*) ; 
 char* xstrfmt (char*,char*) ; 

__attribute__((used)) static char *get_socket_path(void)
{
	struct stat sb;
	char *old_dir, *socket;
	old_dir = expand_user_path("~/.git-credential-cache", 0);
	if (old_dir && !stat(old_dir, &sb) && S_ISDIR(sb.st_mode))
		socket = xstrfmt("%s/socket", old_dir);
	else
		socket = xdg_cache_home("credential/socket");
	free(old_dir);
	return socket;
}