#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  subline ;
typedef  int /*<<< orphan*/  line ;
struct TYPE_2__ {char* fs_spec; char* fs_file; char* fs_type; char* fs_mntops; char* fs_vfstype; void* fs_passno; void* fs_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFTYPE ; 
 void* FSTAB_RO ; 
 void* FSTAB_RQ ; 
 void* FSTAB_RW ; 
 void* FSTAB_SW ; 
 void* FSTAB_XX ; 
 int /*<<< orphan*/  LineNo ; 
 int MAXLINELENGTH ; 
 int /*<<< orphan*/  _fs_fp ; 
 TYPE_1__ _fs_fstab ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixfsfile () ; 
 scalar_t__ strcmp (char*,void*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strpbrk (char*,char*) ; 
 void* strsep (char**,char*) ; 
 scalar_t__ strunvis (char*,char*) ; 

__attribute__((used)) static int
fstabscan(void)
{
	char *cp, *p;
#define	MAXLINELENGTH	1024
	static char line[MAXLINELENGTH];
	char subline[MAXLINELENGTH];
	int typexx;

	for (;;) {

		if (!(p = fgets(line, sizeof(line), _fs_fp)))
			return (0);
/* OLD_STYLE_FSTAB */
		++LineNo;
		if (*line == '#' || *line == '\n')
			continue;
		if (!strpbrk(p, " \t")) {
			_fs_fstab.fs_spec = strsep(&p, ":\n");
			_fs_fstab.fs_file = strsep(&p, ":\n");
			fixfsfile();
			_fs_fstab.fs_type = strsep(&p, ":\n");
			if (_fs_fstab.fs_type) {
				if (!strcmp(_fs_fstab.fs_type, FSTAB_XX))
					continue;
				_fs_fstab.fs_mntops = _fs_fstab.fs_type;
				_fs_fstab.fs_vfstype =
				    strcmp(_fs_fstab.fs_type, FSTAB_SW) ?
				    "ufs" : "swap";
				if ((cp = strsep(&p, ":\n")) != NULL) {
					_fs_fstab.fs_freq = atoi(cp);
					if ((cp = strsep(&p, ":\n")) != NULL) {
						_fs_fstab.fs_passno = atoi(cp);
						return (1);
					}
				}
			}
			goto bad;
		}
/* OLD_STYLE_FSTAB */
		while ((cp = strsep(&p, " \t\n")) != NULL && *cp == '\0')
			;
		_fs_fstab.fs_spec = cp;
		if (_fs_fstab.fs_spec == NULL || *_fs_fstab.fs_spec == '#')
			continue;
		if (strunvis(_fs_fstab.fs_spec, _fs_fstab.fs_spec) < 0)
			goto bad;
		while ((cp = strsep(&p, " \t\n")) != NULL && *cp == '\0')
			;
		_fs_fstab.fs_file = cp;
		if (_fs_fstab.fs_file == NULL)
			goto bad;
		if (strunvis(_fs_fstab.fs_file, _fs_fstab.fs_file) < 0)
			goto bad;
		fixfsfile();
		while ((cp = strsep(&p, " \t\n")) != NULL && *cp == '\0')
			;
		_fs_fstab.fs_vfstype = cp;
		while ((cp = strsep(&p, " \t\n")) != NULL && *cp == '\0')
			;
		_fs_fstab.fs_mntops = cp;
		if (_fs_fstab.fs_mntops == NULL)
			goto bad;
		_fs_fstab.fs_freq = 0;
		_fs_fstab.fs_passno = 0;
		while ((cp = strsep(&p, " \t\n")) != NULL && *cp == '\0')
			;
		if (cp != NULL) {
			_fs_fstab.fs_freq = atoi(cp);
			while ((cp = strsep(&p, " \t\n")) != NULL && *cp == '\0')
				;
			if (cp != NULL)
				_fs_fstab.fs_passno = atoi(cp);
		}
		(void)strlcpy(subline, _fs_fstab.fs_mntops, sizeof(subline));
		p = subline;
		for (typexx = 0, cp = strsep(&p, ","); cp;
		     cp = strsep(&p, ",")) {
			if (strlen(cp) != 2)
				continue;
			if (!strcmp(cp, FSTAB_RW)) {
				_fs_fstab.fs_type = FSTAB_RW;
				break;
			}
			if (!strcmp(cp, FSTAB_RQ)) {
				_fs_fstab.fs_type = FSTAB_RQ;
				break;
			}
			if (!strcmp(cp, FSTAB_RO)) {
				_fs_fstab.fs_type = FSTAB_RO;
				break;
			}
			if (!strcmp(cp, FSTAB_SW)) {
				_fs_fstab.fs_type = FSTAB_SW;
				break;
			}
			if (!strcmp(cp, FSTAB_XX)) {
				_fs_fstab.fs_type = FSTAB_XX;
				typexx++;
				break;
			}
		}
		if (typexx)
			continue;
		if (cp != NULL)
			return (1);

bad:		/* no way to distinguish between EOF and syntax error */
		error(EFTYPE);
	}
	/* NOTREACHED */
}