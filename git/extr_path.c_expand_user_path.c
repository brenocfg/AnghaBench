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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct passwd {char const* pw_dir; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  convert_slashes (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 struct passwd* getpw_str (char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_add_real_path (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchrnul (char const*,char) ; 

char *expand_user_path(const char *path, int real_home)
{
	struct strbuf user_path = STRBUF_INIT;
	const char *to_copy = path;

	if (path == NULL)
		goto return_null;
	if (path[0] == '~') {
		const char *first_slash = strchrnul(path, '/');
		const char *username = path + 1;
		size_t username_len = first_slash - username;
		if (username_len == 0) {
			const char *home = getenv("HOME");
			if (!home)
				goto return_null;
			if (real_home)
				strbuf_add_real_path(&user_path, home);
			else
				strbuf_addstr(&user_path, home);
#ifdef GIT_WINDOWS_NATIVE
			convert_slashes(user_path.buf);
#endif
		} else {
			struct passwd *pw = getpw_str(username, username_len);
			if (!pw)
				goto return_null;
			strbuf_addstr(&user_path, pw->pw_dir);
		}
		to_copy = first_slash;
	}
	strbuf_addstr(&user_path, to_copy);
	return strbuf_detach(&user_path, NULL);
return_null:
	strbuf_release(&user_path);
	return NULL;
}