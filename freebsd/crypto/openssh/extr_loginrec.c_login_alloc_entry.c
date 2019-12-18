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
struct logininfo {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  login_init_entry (struct logininfo*,int /*<<< orphan*/ ,char const*,char const*,char const*) ; 
 struct logininfo* xmalloc (int) ; 

struct
logininfo *login_alloc_entry(pid_t pid, const char *username,
    const char *hostname, const char *line)
{
	struct logininfo *newli;

	newli = xmalloc(sizeof(*newli));
	login_init_entry(newli, pid, username, hostname, line);
	return (newli);
}