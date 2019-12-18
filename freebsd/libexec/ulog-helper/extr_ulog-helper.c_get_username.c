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
typedef  scalar_t__ uid_t ;
struct passwd {scalar_t__ pw_uid; char const* pw_name; } ;

/* Variables and functions */
 char* getlogin () ; 
 struct passwd* getpwnam (char const*) ; 
 struct passwd* getpwuid (scalar_t__) ; 
 scalar_t__ getuid () ; 

__attribute__((used)) static const char *
get_username(void)
{
	const struct passwd *pw;
	const char *login;
	uid_t uid;

	/*
	 * Attempt to determine the username corresponding to this login
	 * session.  First, validate the results of getlogin() against
	 * the password database.  If getlogin() returns invalid data,
	 * return an arbitrary username corresponding to this uid.
	 */
	uid = getuid();
	if ((login = getlogin()) != NULL && (pw = getpwnam(login)) != NULL &&
	    pw->pw_uid == uid)
		return (login);
	if ((pw = getpwuid(uid)) != NULL)
		return (pw->pw_name);
	return (NULL);
}