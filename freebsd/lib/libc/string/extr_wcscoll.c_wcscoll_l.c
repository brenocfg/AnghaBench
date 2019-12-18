#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wchar_t ;
struct xlocale_collate {TYPE_1__* info; scalar_t__ __collate_load_error; } ;
typedef  TYPE_2__* locale_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {scalar_t__* components; } ;
struct TYPE_5__ {int directive_count; int* directive; } ;

/* Variables and functions */
 int COLLATE_MAX_PRIORITY ; 
 int DIRECTIVE_BACKWARD ; 
 int DIRECTIVE_FORWARD ; 
 int DIRECTIVE_POSITION ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FIX_LOCALE (TYPE_2__*) ; 
 size_t XLC_COLLATE ; 
 int /*<<< orphan*/  _collate_lookup (struct xlocale_collate*,scalar_t__ const*,int*,int*,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int wcscmp (scalar_t__ const*,scalar_t__ const*) ; 
 scalar_t__* wcsdup (scalar_t__ const*) ; 
 int wcslen (scalar_t__*) ; 

int
wcscoll_l(const wchar_t *ws1, const wchar_t *ws2, locale_t locale)
{
	int len1, len2, pri1, pri2;
	wchar_t *tr1 = NULL, *tr2 = NULL;
	int direc, pass;
	int ret = wcscmp(ws1, ws2);

	FIX_LOCALE(locale);
	struct xlocale_collate *table =
		(struct xlocale_collate*)locale->components[XLC_COLLATE];

	if (table->__collate_load_error || ret == 0)
		return (ret);

	if (*ws1 == 0 && *ws2 != 0)
		return (-1);
	if (*ws1 != 0 && *ws2 == 0)
		return (1);

	/*
	 * Once upon a time we had code to try to optimize this, but
	 * it turns out that you really can't make many assumptions
	 * safely.  You absolutely have to run this pass by pass,
	 * because some passes will be ignored for a given character,
	 * while others will not.  Simpler locales will benefit from
	 * having fewer passes, and most comparisons should resolve
	 * during the primary pass anyway.
	 *
	 * Note that we do one final extra pass at the end to pick
	 * up UNDEFINED elements.  There is special handling for them.
	 */
	for (pass = 0; pass <= table->info->directive_count; pass++) {

		const int32_t *st1 = NULL;
		const int32_t *st2 = NULL;
		const wchar_t	*w1 = ws1;
		const wchar_t	*w2 = ws2;

		/* special pass for UNDEFINED */
		if (pass == table->info->directive_count) {
			direc = DIRECTIVE_FORWARD;
		} else {
			direc = table->info->directive[pass];
		}

		if (direc & DIRECTIVE_BACKWARD) {
			wchar_t *bp, *fp, c;
			free(tr1);
			if ((tr1 = wcsdup(w1)) == NULL)
				goto end;
			bp = tr1;
			fp = tr1 + wcslen(tr1) - 1;
			while (bp < fp) {
				c = *bp;
				*bp++ = *fp;
				*fp-- = c;
			}
			free(tr2);
			if ((tr2 = wcsdup(w2)) == NULL)
				goto end;
			bp = tr2;
			fp = tr2 + wcslen(tr2) - 1;
			while (bp < fp) {
				c = *bp;
				*bp++ = *fp;
				*fp-- = c;
			}
			w1 = tr1;
			w2 = tr2;
		}

		if (direc & DIRECTIVE_POSITION) {
			int check1, check2;
			while (*w1 && *w2) {
				pri1 = pri2 = 0;
				check1 = check2 = 1;
				while ((pri1 == pri2) && (check1 || check2)) {
					if (check1) {
						_collate_lookup(table, w1, &len1,
						    &pri1, pass, &st1);
						if (pri1 < 0) {
							errno = EINVAL;
							goto end;
						}
						if (!pri1) {
							pri1 = COLLATE_MAX_PRIORITY;
							st1 = NULL;
						}
						check1 = (st1 != NULL);
					}
					if (check2) {
						_collate_lookup(table, w2, &len2,
						    &pri2, pass, &st2);
						if (pri2 < 0) {
							errno = EINVAL;
							goto end;
						}
						if (!pri2) {
							pri2 = COLLATE_MAX_PRIORITY;
							st2 = NULL;
						}
						check2 = (st2 != NULL);
					}
				}
				if (pri1 != pri2) {
					ret = pri1 - pri2;
					goto end;
				}
				w1 += len1;
				w2 += len2;
			}
			if (!*w1) {
				if (*w2) {
					ret = -(int)*w2;
					goto end;
				}
			} else {
				ret = *w1;
				goto end;
			}
		} else {
			int vpri1 = 0, vpri2 = 0;
			while (*w1 || *w2 || st1 || st2) {
				pri1 = 1;
				while (*w1 || st1) {
					_collate_lookup(table, w1, &len1, &pri1,
					    pass, &st1);
					w1 += len1;
					if (pri1 > 0) {
						vpri1++;
						break;
					}

					if (pri1 < 0) {
						errno = EINVAL;
						goto end;
					}
					st1 = NULL;
				}
				pri2 = 1;
				while (*w2 || st2) {
					_collate_lookup(table, w2, &len2, &pri2,
					    pass, &st2);
					w2 += len2;
					if (pri2 > 0) {
						vpri2++;
						break;
					}
					if (pri2 < 0) {
						errno = EINVAL;
						goto end;
					}
					st2 = NULL;
				}
				if ((!pri1 || !pri2) && (vpri1 == vpri2))
					break;
				if (pri1 != pri2) {
					ret = pri1 - pri2;
					goto end;
				}
			}
			if (vpri1 && !vpri2) {
				ret = 1;
				goto end;
			}
			if (!vpri1 && vpri2) {
				ret = -1;
				goto end;
			}
		}
	}
	ret = 0;

end:
	free(tr1);
	free(tr2);

	return (ret);
}