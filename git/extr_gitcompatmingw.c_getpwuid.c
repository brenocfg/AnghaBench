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
typedef  int /*<<< orphan*/  user_name ;
struct passwd {char* pw_name; char* pw_gecos; int /*<<< orphan*/ * pw_dir; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetUserName (char*,int*) ; 
 int /*<<< orphan*/  NameDisplay ; 
 char* get_extended_user_info (int /*<<< orphan*/ ) ; 
 struct passwd* xmalloc (int) ; 

struct passwd *getpwuid(int uid)
{
	static unsigned initialized;
	static char user_name[100];
	static struct passwd *p;
	DWORD len;

	if (initialized)
		return p;

	len = sizeof(user_name);
	if (!GetUserName(user_name, &len)) {
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