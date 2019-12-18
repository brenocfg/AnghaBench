#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dirent_prec_psx {size_t max_name_len; char* d_name; int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_ino; } ;
struct dirent {int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_ino; } ;
typedef  scalar_t__ iconv_t ;
typedef  int /*<<< orphan*/  iconv_ibp ;
typedef  int /*<<< orphan*/  dirent_prec_psx ;
struct TYPE_3__ {scalar_t__ ic_precompose; struct dirent_prec_psx* dirent_nfc; int /*<<< orphan*/  dirp; } ;
typedef  TYPE_1__ PREC_DIR ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ has_non_ascii (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iconv (scalar_t__,int /*<<< orphan*/ *,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  path_encoding ; 
 int precomposed_unicode ; 
 struct dirent* readdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_encoding ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 struct dirent_prec_psx* xrealloc (struct dirent_prec_psx*,size_t) ; 

struct dirent_prec_psx *precompose_utf8_readdir(PREC_DIR *prec_dir)
{
	struct dirent *res;
	res = readdir(prec_dir->dirp);
	if (res) {
		size_t namelenz = strlen(res->d_name) + 1; /* \0 */
		size_t new_maxlen = namelenz;

		int ret_errno = errno;

		if (new_maxlen > prec_dir->dirent_nfc->max_name_len) {
			size_t new_len = sizeof(dirent_prec_psx) + new_maxlen -
				sizeof(prec_dir->dirent_nfc->d_name);

			prec_dir->dirent_nfc = xrealloc(prec_dir->dirent_nfc, new_len);
			prec_dir->dirent_nfc->max_name_len = new_maxlen;
		}

		prec_dir->dirent_nfc->d_ino  = res->d_ino;
		prec_dir->dirent_nfc->d_type = res->d_type;

		if ((precomposed_unicode == 1) && has_non_ascii(res->d_name, (size_t)-1, NULL)) {
			if (prec_dir->ic_precompose == (iconv_t)-1) {
				die("iconv_open(%s,%s) failed, but needed:\n"
						"    precomposed unicode is not supported.\n"
						"    If you want to use decomposed unicode, run\n"
						"    \"git config core.precomposeunicode false\"\n",
						repo_encoding, path_encoding);
			} else {
				iconv_ibp	cp = (iconv_ibp)res->d_name;
				size_t inleft = namelenz;
				char *outpos = &prec_dir->dirent_nfc->d_name[0];
				size_t outsz = prec_dir->dirent_nfc->max_name_len;
				errno = 0;
				iconv(prec_dir->ic_precompose, &cp, &inleft, &outpos, &outsz);
				if (errno || inleft) {
					/*
					 * iconv() failed and errno could be E2BIG, EILSEQ, EINVAL, EBADF
					 * MacOS X avoids illegal byte sequences.
					 * If they occur on a mounted drive (e.g. NFS) it is not worth to
					 * die() for that, but rather let the user see the original name
					*/
					namelenz = 0; /* trigger strlcpy */
				}
			}
		} else
			namelenz = 0;

		if (!namelenz)
			strlcpy(prec_dir->dirent_nfc->d_name, res->d_name,
							prec_dir->dirent_nfc->max_name_len);

		errno = ret_errno;
		return prec_dir->dirent_nfc;
	}
	return NULL;
}