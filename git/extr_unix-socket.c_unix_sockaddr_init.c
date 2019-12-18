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
struct unix_sockaddr_context {int /*<<< orphan*/ * orig_dir; } ;
struct strbuf {int dummy; } ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ chdir_len (char const*,int) ; 
 int /*<<< orphan*/  errno ; 
 char* find_last_dir_sep (char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ strbuf_getcwd (struct strbuf*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int unix_sockaddr_init(struct sockaddr_un *sa, const char *path,
			      struct unix_sockaddr_context *ctx)
{
	int size = strlen(path) + 1;

	ctx->orig_dir = NULL;
	if (size > sizeof(sa->sun_path)) {
		const char *slash = find_last_dir_sep(path);
		const char *dir;
		struct strbuf cwd = STRBUF_INIT;

		if (!slash) {
			errno = ENAMETOOLONG;
			return -1;
		}

		dir = path;
		path = slash + 1;
		size = strlen(path) + 1;
		if (size > sizeof(sa->sun_path)) {
			errno = ENAMETOOLONG;
			return -1;
		}
		if (strbuf_getcwd(&cwd))
			return -1;
		ctx->orig_dir = strbuf_detach(&cwd, NULL);
		if (chdir_len(dir, slash - dir) < 0)
			return -1;
	}

	memset(sa, 0, sizeof(*sa));
	sa->sun_family = AF_UNIX;
	memcpy(sa->sun_path, path, size);
	return 0;
}