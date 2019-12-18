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
struct iconv_hooks {int dummy; } ;
struct _citrus_iconv {TYPE_1__* cv_shared; } ;
typedef  scalar_t__ iconv_t ;
struct TYPE_2__ {char* ci_convname; int ci_discard_ilseq; int ci_ilseq_invalid; struct iconv_hooks* ci_hooks; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
#define  ICONV_GET_DISCARD_ILSEQ 136 
#define  ICONV_GET_ILSEQ_INVALID 135 
#define  ICONV_GET_TRANSLITERATE 134 
#define  ICONV_SET_DISCARD_ILSEQ 133 
#define  ICONV_SET_FALLBACKS 132 
#define  ICONV_SET_HOOKS 131 
#define  ICONV_SET_ILSEQ_INVALID 130 
#define  ICONV_SET_TRANSLITERATE 129 
#define  ICONV_TRIVIALP 128 
 scalar_t__ ISBADF (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcmp (char const*,char*,size_t) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char*) ; 

int
__bsd_iconvctl(iconv_t cd, int request, void *argument)
{
	struct _citrus_iconv *cv;
	struct iconv_hooks *hooks;
	const char *convname;
	char *dst;
	int *i;
	size_t srclen;

	cv = (struct _citrus_iconv *)(void *)cd;
	hooks = (struct iconv_hooks *)argument;
	i = (int *)argument;

	if (ISBADF(cd)) {
		errno = EBADF;
		return (-1);
	}

	switch (request) {
	case ICONV_TRIVIALP:
		convname = cv->cv_shared->ci_convname;
		dst = strchr(convname, '/');
		srclen = dst - convname;
		dst++;
		*i = (srclen == strlen(dst)) && !memcmp(convname, dst, srclen);
		return (0);
	case ICONV_GET_TRANSLITERATE:
		*i = 1;
		return (0);
	case ICONV_SET_TRANSLITERATE:
		return  ((*i == 1) ? 0 : -1);
	case ICONV_GET_DISCARD_ILSEQ:
		*i = cv->cv_shared->ci_discard_ilseq ? 1 : 0;
		return (0);
	case ICONV_SET_DISCARD_ILSEQ:
		cv->cv_shared->ci_discard_ilseq = *i;
		return (0);
	case ICONV_SET_HOOKS:
		cv->cv_shared->ci_hooks = hooks;
		return (0);
	case ICONV_SET_FALLBACKS:
		errno = EOPNOTSUPP;
		return (-1);
	case ICONV_GET_ILSEQ_INVALID:
		*i = cv->cv_shared->ci_ilseq_invalid ? 1 : 0;
		return (0);
	case ICONV_SET_ILSEQ_INVALID:
		cv->cv_shared->ci_ilseq_invalid = *i;
		return (0);
	default:
		errno = EINVAL;
		return (-1);
	}
}