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
struct config_strlist {char* str; struct config_strlist* next; } ;
struct config_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_chroot_string (char const*,char**,char const*,struct config_file*) ; 
 char* fname_after_chroot (char*,struct config_file*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strchr (char*,char) ; 

__attribute__((used)) static void
check_chroot_filelist_wild(const char* desc, struct config_strlist* list,
	const char* chrootdir, struct config_file* cfg)
{
	struct config_strlist* p;
	for(p=list; p; p=p->next) {
#ifdef HAVE_GLOB
		if(strchr(p->str, '*') || strchr(p->str, '[') ||
			strchr(p->str, '?') || strchr(p->str, '{') ||
			strchr(p->str, '~')) {
			char* s = p->str;
			/* adjust whole pattern for chroot and check later */
			p->str = fname_after_chroot(p->str, cfg, 1);
			free(s);
		} else
#endif /* HAVE_GLOB */
			check_chroot_string(desc, &p->str, chrootdir, cfg);
	}
}