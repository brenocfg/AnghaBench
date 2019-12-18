#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int hi; int /*<<< orphan*/  lo; } ;
struct TYPE_6__ {void* lh; void* ll; } ;
struct TYPE_8__ {int Q_s; TYPE_2__ D_s; TYPE_1__ W_s; } ;
typedef  TYPE_3__ vint64 ;
typedef  int uint32_t ;
typedef  void* uint16_t ;
typedef  char u_char ;
typedef  int /*<<< orphan*/  res ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  M_ADD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  M_NEG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ isdigit (char const) ; 
 scalar_t__ islower (char const) ; 
 scalar_t__ isspace (char const) ; 
 scalar_t__ isupper (char const) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int,int) ; 
 scalar_t__ noconst (char const*) ; 
 char toupper (char const) ; 

vint64
strtouv64(
	const char * begp,
	char **      endp,
	int          base
	)
{
	vint64  res;
	u_char  digit;
	int     sig, num;
	const u_char *src;
	
	num = sig = 0;
	src = (const u_char*)begp;
	while (isspace(*src))
		src++;

	if (*src == '-') {
		src++;
		sig = 1;
	} else  if (*src == '+') {
		src++;
	}

	if (base == 0) {
		base = 10;
		if (*src == '0') {
			base = 8;
			if (toupper(*++src) == 'X') {
				src++;
				base = 16;
			}
		}
	} else if (base == 16) { /* remove optional leading '0x' or '0X' */
		if (src[0] == '0' && toupper(src[1]) == 'X')
			src += 2;
	} else if (base <= 2 || base > 36) {
		memset(&res, 0xFF, sizeof(res));
		errno = ERANGE;
		return res;
	}
	
	memset(&res, 0, sizeof(res));
	while (*src) {
		if (isdigit(*src))
			digit = *src - '0';
		else if (isupper(*src))
			digit = *src - 'A' + 10;
		else if (islower(*src))
			digit = *src - 'a' + 10;
		else
			break;
		if (digit >= base)
			break;
		num = 1;
#if defined(HAVE_INT64)
		res.Q_s = res.Q_s * base + digit;
#else
		/* res *= base, using 16x16->32 bit
		 * multiplication. Slow but portable.
		 */ 
		{
			uint32_t accu;
			accu       = (uint32_t)res.W_s.ll * base;
			res.W_s.ll = (uint16_t)accu;
			accu       = (accu >> 16)
			           + (uint32_t)res.W_s.lh * base;
			res.W_s.lh = (uint16_t)accu;
			/* the upper bits can be done in one step: */
			res.D_s.hi = res.D_s.hi * base + (accu >> 16);
		}
		M_ADD(res.D_s.hi, res.D_s.lo, 0, digit);
#endif
		src++;
	}
	if (!num)
		errno = EINVAL;
	if (endp)
		*endp = (char*)noconst(src);
	if (sig)
		M_NEG(res.D_s.hi, res.D_s.lo);
	return res;
}