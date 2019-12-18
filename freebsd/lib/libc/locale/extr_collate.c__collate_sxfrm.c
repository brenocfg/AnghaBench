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
typedef  void* wchar_t ;
typedef  void* uint8_t ;
struct xlocale_collate {TYPE_1__* info; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int directive_count; int* directive; } ;

/* Variables and functions */
 int COLLATE_MAX_PRIORITY ; 
 int DIRECTIVE_BACKWARD ; 
 int DIRECTIVE_FORWARD ; 
 int DIRECTIVE_POSITION ; 
 int DIRECTIVE_UNDEFINED ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int XFRM_BYTES ; 
 int /*<<< orphan*/  XFRM_SEP ; 
 int /*<<< orphan*/  _collate_lookup (struct xlocale_collate*,void* const*,int*,int*,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  assert (void* const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (void**) ; 
 void** wcsdup (void* const*) ; 
 int wcslen (void**) ; 
 int xfrm (struct xlocale_collate*,void**,int,int) ; 

size_t
_collate_sxfrm(struct xlocale_collate *table, const wchar_t *src, char *xf,
    size_t room)
{
	int		pri;
	int		len;
	const wchar_t	*t;
	wchar_t		*tr = NULL;
	int		direc;
	int		pass;
	const int32_t 	*state;
	size_t		want = 0;
	size_t		need = 0;
	int		b;
	uint8_t		buf[XFRM_BYTES];
	int		ndir = table->info->directive_count;

	assert(src);

	for (pass = 0; pass <= ndir; pass++) {

		state = NULL;

		if (pass != 0) {
			/* insert level separator from the previous pass */
			if (room) {
				*xf++ = XFRM_SEP;
				room--;
			}
			want++;
		}

		/* special pass for undefined */
		if (pass == ndir) {
			direc = DIRECTIVE_FORWARD | DIRECTIVE_UNDEFINED;
		} else {
			direc = table->info->directive[pass];
		}

		t = src;

		if (direc & DIRECTIVE_BACKWARD) {
			wchar_t *bp, *fp, c;
			free(tr);
			if ((tr = wcsdup(t)) == NULL) {
				errno = ENOMEM;
				goto fail;
			}
			bp = tr;
			fp = tr + wcslen(tr) - 1;
			while (bp < fp) {
				c = *bp;
				*bp++ = *fp;
				*fp-- = c;
			}
			t = (const wchar_t *)tr;
		}

		if (direc & DIRECTIVE_POSITION) {
			while (*t || state) {

				_collate_lookup(table, t, &len, &pri, pass, &state);
				t += len;
				if (pri <= 0) {
					if (pri < 0) {
						errno = EINVAL;
						goto fail;
					}
					state = NULL;
					pri = COLLATE_MAX_PRIORITY;
				}

				b = xfrm(table, buf, pri, pass);
				want += b;
				if (room) {
					while (b) {
						b--;
						if (room) {
							*xf++ = buf[b];
							room--;
						}
					}
				}
				need = want;
			}
		} else {
			while (*t || state) {
				_collate_lookup(table, t, &len, &pri, pass, &state);
				t += len;
				if (pri <= 0) {
					if (pri < 0) {
						errno = EINVAL;
						goto fail;
					}
					state = NULL;
					continue;
				}

				b = xfrm(table, buf, pri, pass);
				want += b;
				if (room) {

					while (b) {
						b--;
						if (room) {
							*xf++ = buf[b];
							room--;
						}
					}
				}
				need = want;
			}
		}
	}
	free(tr);
	return (need);

fail:
	free(tr);
	return ((size_t)(-1));
}