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
struct strbuf {int dummy; } ;
struct passwd {int /*<<< orphan*/ * pw_name; } ;

/* Variables and functions */
 char* get_gecos (struct passwd const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ *) ; 
 int toupper (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_gecos(const struct passwd *w, struct strbuf *name)
{
	char *src;

	/* Traditionally GECOS field had office phone numbers etc, separated
	 * with commas.  Also & stands for capitalized form of the login name.
	 */

	for (src = get_gecos(w); *src && *src != ','; src++) {
		int ch = *src;
		if (ch != '&')
			strbuf_addch(name, ch);
		else {
			/* Sorry, Mr. McDonald... */
			strbuf_addch(name, toupper(*w->pw_name));
			strbuf_addstr(name, w->pw_name + 1);
		}
	}
}