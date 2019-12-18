#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
struct TYPE_9__ {int start; int end; } ;
typedef  TYPE_1__ range_t ;
struct TYPE_10__ {scalar_t__ charset; int length; } ;
typedef  TYPE_2__ graphic_t ;
typedef  int /*<<< orphan*/  escape_t ;
struct TYPE_11__ {int chlen; int* ch; int /*<<< orphan*/ * inuse; } ;
typedef  TYPE_3__ _HZState ;
typedef  int /*<<< orphan*/  _HZEncodingInfo ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 
 int ESC (int /*<<< orphan*/ *) ; 
 int ESCAPE_CHAR ; 
 scalar_t__ GB2312 ; 
 TYPE_2__* GL (int /*<<< orphan*/ *) ; 
 TYPE_2__* GR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * INIT0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * INIT1 (int /*<<< orphan*/ *) ; 
 int MB_LEN_MAX ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _citrus_HZ_init_state (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * find_escape (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ranges ; 

__attribute__((used)) static int
_citrus_HZ_mbrtowc_priv(_HZEncodingInfo * __restrict ei,
    wchar_t * __restrict pwc, char ** __restrict s, size_t n,
    _HZState * __restrict psenc, size_t * __restrict nresult)
{
	escape_t *candidate, *init;
	graphic_t *graphic;
	const range_t *range;
	char *s0;
	wchar_t wc;
	int bit, ch, head, len, tail;

	if (*s == NULL) {
		_citrus_HZ_init_state(ei, psenc);
		*nresult = 1;
		return (0);
	}
	s0 = *s;
	if (psenc->chlen < 0 || psenc->inuse == NULL)
		return (EINVAL);

	wc = (wchar_t)0;
	bit = head = tail = 0;
	graphic = NULL;
	for (len = 0; len <= MB_LEN_MAX;) {
		if (psenc->chlen == tail) {
			if (n-- < 1) {
				*s = s0;
				*nresult = (size_t)-2;
				return (0);
			}
			psenc->ch[psenc->chlen++] = *s0++;
			++len;
		}
		ch = (unsigned char)psenc->ch[tail++];
		if (tail == 1) {
			if ((ch & ~0x80) <= 0x1F) {
				if (psenc->inuse != INIT0(ei))
					break;
				wc = (wchar_t)ch;
				goto done;
			}
			if (ch & 0x80) {
				graphic = GR(psenc->inuse);
				bit = 0x80;
				ch &= ~0x80;
			} else {
				graphic = GL(psenc->inuse);
				if (ch == ESCAPE_CHAR)
					continue;
				bit = 0x0;
			}
			if (graphic == NULL)
				break;
		} else if (tail == 2 && psenc->ch[0] == ESCAPE_CHAR) {
			if (tail < psenc->chlen)
				return (EINVAL);
			if (ch == ESCAPE_CHAR) {
				++head;
			} else if (ch == '\n') {
				if (psenc->inuse != INIT0(ei))
					break;
				tail = psenc->chlen = 0;
				continue;
			} else {
				candidate = NULL;
				init = INIT0(ei);
				if (psenc->inuse == init) {
					init = INIT1(ei);
				} else if (INIT(psenc->inuse) == init) {
					if (ESC(init) != ch)
						break;
					candidate = init;
				}
				if (candidate == NULL) {
					candidate = find_escape(
					    SET(psenc->inuse), ch);
					if (candidate == NULL) {
						if (init == NULL ||
						    ESC(init) != ch)
							break;
						candidate = init;
					}
				}
				psenc->inuse = candidate;
				tail = psenc->chlen = 0;
				continue;
			}
		} else if (ch & 0x80) {
			if (graphic != GR(psenc->inuse))
				break;
			ch &= ~0x80;
		} else {
			if (graphic != GL(psenc->inuse))
				break;
		}
		range = &ranges[(size_t)graphic->charset];
		if (range->start > ch || range->end < ch)
			break;
		wc <<= 8;
		wc |= ch;
		if (graphic->length == (tail - head)) {
			if (graphic->charset > GB2312)
				bit |= ESC(psenc->inuse) << 24;
			wc |= bit;
			goto done;
		}
	}
	*nresult = (size_t)-1;
	return (EILSEQ);
done:
	if (tail < psenc->chlen)
		return (EINVAL);
	*s = s0;
	if (pwc != NULL)
		*pwc = wc;
	psenc->chlen = 0;
	*nresult = (wc == 0) ? 0 : len;

	return (0);
}