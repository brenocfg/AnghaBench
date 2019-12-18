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
struct mount {int dummy; } ;

/* Variables and functions */
#define  A_CONTINUE 131 
#define  A_PANIC 130 
#define  A_REBOOT 129 
#define  A_RETRY 128 
 char CC_NONWHITESPACE ; 
 int EDOOFUS ; 
 int PE_EOL ; 
 int /*<<< orphan*/  RB_NOSYNC ; 
 struct mount* TAILQ_NEXT (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kern_reboot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_list ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  parse_advance (char**) ; 
 int parse_directive (char**) ; 
 int parse_mount (char**) ; 
 char parse_peek (char**) ; 
 int parse_skipto (char**,char) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int root_mount_mddev ; 
 int root_mount_onfail ; 
 char* sbuf_data (struct sbuf*) ; 

__attribute__((used)) static int
vfs_mountroot_parse(struct sbuf *sb, struct mount *mpdevfs)
{
	struct mount *mp;
	char *conf;
	int error;

	root_mount_mddev = -1;

retry:
	conf = sbuf_data(sb);
	mp = TAILQ_NEXT(mpdevfs, mnt_list);
	error = (mp == NULL) ? 0 : EDOOFUS;
	root_mount_onfail = A_CONTINUE;
	while (mp == NULL) {
		error = parse_skipto(&conf, CC_NONWHITESPACE);
		if (error == PE_EOL) {
			parse_advance(&conf);
			continue;
		}
		if (error < 0)
			break;
		switch (parse_peek(&conf)) {
		case '#':
			error = parse_skipto(&conf, '\n');
			break;
		case '.':
			error = parse_directive(&conf);
			break;
		default:
			error = parse_mount(&conf);
			if (error == -1) {
				printf("mountroot: invalid file system "
				    "specification.\n");
				error = 0;
			}
			break;
		}
		if (error < 0)
			break;
		/* Ignore any trailing garbage on the line. */
		if (parse_peek(&conf) != '\n') {
			printf("mountroot: advancing to next directive...\n");
			(void)parse_skipto(&conf, '\n');
		}
		mp = TAILQ_NEXT(mpdevfs, mnt_list);
	}
	if (mp != NULL)
		return (0);

	/*
	 * We failed to mount (a new) root.
	 */
	switch (root_mount_onfail) {
	case A_CONTINUE:
		break;
	case A_PANIC:
		panic("mountroot: unable to (re-)mount root.");
		/* NOTREACHED */
	case A_RETRY:
		goto retry;
	case A_REBOOT:
		kern_reboot(RB_NOSYNC);
		/* NOTREACHED */
	}

	return (error);
}