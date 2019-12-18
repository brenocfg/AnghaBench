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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int chlen; int mode; int bits; int cache; scalar_t__* ch; } ;
typedef  TYPE_1__ _UTF7State ;
typedef  int /*<<< orphan*/  _UTF7EncodingInfo ;

/* Variables and functions */
 int BASE64_BIT ; 
 scalar_t__ BASE64_IN ; 
 scalar_t__ BASE64_OUT ; 
 int EILSEQ ; 
 int EINVAL ; 
 int FINDLEN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISDIRECT (int /*<<< orphan*/ *,int) ; 
 scalar_t__ SHIFT7BIT (int) ; 
 int /*<<< orphan*/  UTF16_BIT ; 
 scalar_t__ UTF16_MAX ; 

__attribute__((used)) static int
_citrus_UTF7_mbtoutf16(_UTF7EncodingInfo * __restrict ei,
    uint16_t * __restrict u16, char ** __restrict s, size_t n,
    _UTF7State * __restrict psenc, size_t * __restrict nresult)
{
	char *s0;
	int done, i, len;

	*nresult = 0;
	s0 = *s;

	for (i = 0, done = 0; done == 0; i++) {
		if (i == psenc->chlen) {
			if (n-- < 1) {
				*nresult = (size_t)-2;
				*s = s0;
				return (0);
			}
			psenc->ch[psenc->chlen++] = *s0++;
		}
		if (SHIFT7BIT((int)psenc->ch[i]))
			goto ilseq;
		if (!psenc->mode) {
			if (psenc->bits > 0 || psenc->cache > 0)
				return (EINVAL);
			if (psenc->ch[i] == BASE64_IN)
				psenc->mode = 1;
			else {
				if (!ISDIRECT(ei, (int)psenc->ch[i]))
					goto ilseq;
				*u16 = (uint16_t)psenc->ch[i];
				done = 1;
				continue;
			}
		} else {
			if (psenc->ch[i] == BASE64_OUT && psenc->cache == 0) {
				psenc->mode = 0;
				*u16 = (uint16_t)BASE64_IN;
				done = 1;
				continue;
			}
			len = FINDLEN(ei, (int)psenc->ch[i]);
			if (len < 0) {
				if (psenc->bits >= BASE64_BIT)
					return (EINVAL);
				psenc->mode = 0;
				psenc->bits = psenc->cache = 0;
				if (psenc->ch[i] != BASE64_OUT) {
					if (!ISDIRECT(ei, (int)psenc->ch[i]))
						goto ilseq;
					*u16 = (uint16_t)psenc->ch[i];
					done = 1;
				} else {
					psenc->chlen--;
					i--;
				}
			} else {
				psenc->cache =
				    (psenc->cache << BASE64_BIT) | len;
				switch (psenc->bits) {
				case 0: case 2: case 4: case 6: case 8:
					psenc->bits += BASE64_BIT;
					break;
				case 10: case 12: case 14:
					psenc->bits -= (UTF16_BIT - BASE64_BIT);
					*u16 = (psenc->cache >> psenc->bits) &
					    UTF16_MAX;
					done = 1;
					break;
				default:
					return (EINVAL);
				}
			}
		}
	}

	if (psenc->chlen > i)
		return (EINVAL);
	psenc->chlen = 0;
	*nresult = (size_t)((*u16 == 0) ? 0 : s0 - *s);
	*s = s0;

	return (0);

ilseq:
	*nresult = (size_t)-1;
	return (EILSEQ);
}