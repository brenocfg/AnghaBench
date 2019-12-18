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

/* Variables and functions */
 int KT_MAX ; 
 int KT_MIN ; 
 scalar_t__ MAXCON ; 
 int /*<<< orphan*/  conalloc (char*,char*,int) ; 
 int /*<<< orphan*/  conloop () ; 
 int get_keytypes ; 
 scalar_t__ ncon ; 
 char* strnnsep (char**,char*) ; 

__attribute__((used)) static void
do_host(char *host)
{
	char *name = strnnsep(&host, " \t\n");
	int j;

	if (name == NULL)
		return;
	for (j = KT_MIN; j <= KT_MAX; j *= 2) {
		if (get_keytypes & j) {
			while (ncon >= MAXCON)
				conloop();
			conalloc(name, *host ? host : name, j);
		}
	}
}