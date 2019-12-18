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
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int RB_ASKNAME ; 
 int RB_CDROM ; 
 int RB_DFLTROOT ; 
 int /*<<< orphan*/  ROOTDEVNAME ; 
 int boothowto ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeenv (char*) ; 
 char* kern_getenv (char*) ; 
 int parse_token (char**,char**) ; 
 int /*<<< orphan*/  root_mount_timeout ; 
 int /*<<< orphan*/ ** rootdevnames ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 

__attribute__((used)) static void
vfs_mountroot_conf0(struct sbuf *sb)
{
	char *s, *tok, *mnt, *opt;
	int error;

	sbuf_printf(sb, ".onfail panic\n");
	sbuf_printf(sb, ".timeout %d\n", root_mount_timeout);
	if (boothowto & RB_ASKNAME)
		sbuf_printf(sb, ".ask\n");
#ifdef ROOTDEVNAME
	if (boothowto & RB_DFLTROOT)
		sbuf_printf(sb, "%s\n", ROOTDEVNAME);
#endif
	if (boothowto & RB_CDROM) {
		sbuf_printf(sb, "cd9660:/dev/cd0 ro\n");
		sbuf_printf(sb, ".timeout 0\n");
		sbuf_printf(sb, "cd9660:/dev/cd1 ro\n");
		sbuf_printf(sb, ".timeout %d\n", root_mount_timeout);
	}
	s = kern_getenv("vfs.root.mountfrom");
	if (s != NULL) {
		opt = kern_getenv("vfs.root.mountfrom.options");
		tok = s;
		error = parse_token(&tok, &mnt);
		while (!error) {
			sbuf_printf(sb, "%s %s\n", mnt,
			    (opt != NULL) ? opt : "");
			free(mnt, M_TEMP);
			error = parse_token(&tok, &mnt);
		}
		if (opt != NULL)
			freeenv(opt);
		freeenv(s);
	}
	if (rootdevnames[0] != NULL)
		sbuf_printf(sb, "%s\n", rootdevnames[0]);
	if (rootdevnames[1] != NULL)
		sbuf_printf(sb, "%s\n", rootdevnames[1]);
#ifdef ROOTDEVNAME
	if (!(boothowto & RB_DFLTROOT))
		sbuf_printf(sb, "%s\n", ROOTDEVNAME);
#endif
	if (!(boothowto & RB_ASKNAME))
		sbuf_printf(sb, ".ask\n");
}