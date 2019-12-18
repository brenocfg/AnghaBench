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
struct stat {int st_size; } ;
struct futx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZ ; 
 int /*<<< orphan*/  EFTYPE ; 
 int /*<<< orphan*/  EINVAL ; 
#define  UTXDB_ACTIVE 130 
#define  UTXDB_LASTLOGIN 129 
#define  UTXDB_LOG 128 
 int /*<<< orphan*/  _IOFBF ; 
 char* _PATH_UTX_ACTIVE ; 
 char* _PATH_UTX_LASTLOGIN ; 
 char* _PATH_UTX_LOG ; 
 int _fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  rounddown (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int udb ; 
 int /*<<< orphan*/ * uf ; 

int
setutxdb(int db, const char *file)
{
	struct stat sb;

	switch (db) {
	case UTXDB_ACTIVE:
		if (file == NULL)
			file = _PATH_UTX_ACTIVE;
		break;
	case UTXDB_LASTLOGIN:
		if (file == NULL)
			file = _PATH_UTX_LASTLOGIN;
		break;
	case UTXDB_LOG:
		if (file == NULL)
			file = _PATH_UTX_LOG;
		break;
	default:
		errno = EINVAL;
		return (-1);
	}

	if (uf != NULL)
		fclose(uf);
	uf = fopen(file, "re");
	if (uf == NULL)
		return (-1);

	if (db != UTXDB_LOG) {
		/* Safety check: never use broken files. */
		if (_fstat(fileno(uf), &sb) != -1 &&
		    sb.st_size % sizeof(struct futx) != 0) {
			fclose(uf);
			uf = NULL;
			errno = EFTYPE;
			return (-1);
		}
		/* Prevent reading of partial records. */
		(void)setvbuf(uf, NULL, _IOFBF,
		    rounddown(BUFSIZ, sizeof(struct futx)));
	}

	udb = db;
	return (0);
}