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
struct thread {int dummy; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strstr (char*,char*) ; 
 char* version ; 

__attribute__((used)) static void
linprocfs_osbuilder(struct thread *td, struct sbuf *sb)
{
#if 0
	char builder[256];
	char *cp;

	cp = strstr(version, "\n    ");
	if (cp) {
		strncpy(builder, cp + 5, 256);
		builder[255] = '\0';
		cp = strstr(builder, ":");
		if (cp)
			*cp = '\0';
	}
	if (cp)
		sbuf_cat(sb, builder);
	else
#endif
		sbuf_cat(sb, "des@freebsd.org");
}