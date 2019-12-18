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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  user_name ;
struct passwd {char* pw_name; char* pw_gecos; int /*<<< orphan*/ * pw_dir; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetUserNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NameDisplay ; 
 char* get_extended_user_info (int /*<<< orphan*/ ) ; 
 struct passwd* xmalloc (int) ; 
 scalar_t__ xwcstoutf (char*,int /*<<< orphan*/ *,int) ; 

struct passwd *getpwuid(int uid)
{
	static unsigned initialized;
	static char user_name[100];
	static struct passwd *p;
	wchar_t buf[100];
	DWORD len;

	if (initialized)
		return p;

	len = ARRAY_SIZE(buf);
	if (!GetUserNameW(buf, &len)) {
		initialized = 1;
		return NULL;
	}

	if (xwcstoutf(user_name, buf, sizeof(user_name)) < 0) {
		initialized = 1;
		return NULL;
	}

	p = xmalloc(sizeof(*p));
	p->pw_name = user_name;
	p->pw_gecos = get_extended_user_info(NameDisplay);
	if (!p->pw_gecos)
		p->pw_gecos = "unknown";
	p->pw_dir = NULL;

	initialized = 1;
	return p;
}