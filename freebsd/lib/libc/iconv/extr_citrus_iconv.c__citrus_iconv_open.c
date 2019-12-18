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
struct _citrus_iconv_shared {TYPE_1__* ci_ops; } ;
struct _citrus_iconv {struct _citrus_iconv_shared* cv_shared; } ;
typedef  int /*<<< orphan*/  path ;
struct TYPE_2__ {int (* io_init_context ) (struct _citrus_iconv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CODESET ; 
 int EINVAL ; 
 int PATH_MAX ; 
 char* _CITRUS_ICONV_ALIAS ; 
 int /*<<< orphan*/  _LOOKUP_CASE_IGNORE ; 
 char* _PATH_ICONV ; 
 char const* _lookup_alias (char*,char const*,char*,size_t,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct _citrus_iconv*) ; 
 int get_shared (struct _citrus_iconv_shared**,char*,char*) ; 
 int /*<<< orphan*/  init_cache () ; 
 struct _citrus_iconv* malloc (int) ; 
 char* nl_langinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_shared (struct _citrus_iconv_shared*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 int stub1 (struct _citrus_iconv*) ; 

int
_citrus_iconv_open(struct _citrus_iconv * __restrict * __restrict rcv,
    const char * __restrict src, const char * __restrict dst)
{
	struct _citrus_iconv *cv = NULL;
	struct _citrus_iconv_shared *ci = NULL;
	char realdst[PATH_MAX], realsrc[PATH_MAX];
#ifdef _PATH_ICONV
	char buf[PATH_MAX], path[PATH_MAX];
#endif
	int ret;

	init_cache();

	/* GNU behaviour, using locale encoding if "" or "char" is specified */
	if ((strcmp(src, "") == 0) || (strcmp(src, "char") == 0))
		src = nl_langinfo(CODESET);
	if ((strcmp(dst, "") == 0) || (strcmp(dst, "char") == 0))
		dst = nl_langinfo(CODESET);

	/* resolve codeset name aliases */
#ifdef _PATH_ICONV
	snprintf(path, sizeof(path), "%s/%s", _PATH_ICONV, _CITRUS_ICONV_ALIAS);
	strlcpy(realsrc, _lookup_alias(path, src, buf, (size_t)PATH_MAX,
	    _LOOKUP_CASE_IGNORE), (size_t)PATH_MAX);
	strlcpy(realdst, _lookup_alias(path, dst, buf, (size_t)PATH_MAX,
	    _LOOKUP_CASE_IGNORE), (size_t)PATH_MAX);
#else
	strlcpy(realsrc, src, (size_t)PATH_MAX);
	strlcpy(realdst, dst, (size_t)PATH_MAX);
#endif

	/* sanity check */
	if (strchr(realsrc, '/') != NULL || strchr(realdst, '/'))
		return (EINVAL);

	/* get shared record */
	ret = get_shared(&ci, realsrc, realdst);
	if (ret)
		return (ret);

	/* create/init context */
	if (*rcv == NULL) {
		cv = malloc(sizeof(*cv));
		if (cv == NULL) {
			ret = errno;
			release_shared(ci);
			return (ret);
		}
		*rcv = cv;
	}
	(*rcv)->cv_shared = ci;
	ret = (*ci->ci_ops->io_init_context)(*rcv);
	if (ret) {
		release_shared(ci);
		free(cv);
		return (ret);
	}
	return (0);
}