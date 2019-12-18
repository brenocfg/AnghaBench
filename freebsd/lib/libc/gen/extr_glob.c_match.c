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
struct xlocale_collate {int /*<<< orphan*/  __collate_load_error; } ;
struct TYPE_2__ {scalar_t__* components; } ;
typedef  int Char ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR (int) ; 
 int EOS ; 
#define  M_ALL 130 
 int M_END ; 
 int M_MASK ; 
 int M_NOT ; 
#define  M_ONE 129 
 int M_RNG ; 
#define  M_SET 128 
 size_t XLC_COLLATE ; 
 TYPE_1__* __get_locale () ; 
 int /*<<< orphan*/  __wcollate_range_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
match(Char *name, Char *pat, Char *patend)
{
	int ok, negate_range;
	Char c, k, *nextp, *nextn;
	struct xlocale_collate *table =
		(struct xlocale_collate*)__get_locale()->components[XLC_COLLATE];

	nextn = NULL;
	nextp = NULL;

	while (1) {
		while (pat < patend) {
			c = *pat++;
			switch (c & M_MASK) {
			case M_ALL:
				if (pat == patend)
					return (1);
				if (*name == EOS)
					return (0);
				nextn = name + 1;
				nextp = pat - 1;
				break;
			case M_ONE:
				if (*name++ == EOS)
					goto fail;
				break;
			case M_SET:
				ok = 0;
				if ((k = *name++) == EOS)
					goto fail;
				negate_range = ((*pat & M_MASK) == M_NOT);
				if (negate_range != 0)
					++pat;
				while (((c = *pat++) & M_MASK) != M_END)
					if ((*pat & M_MASK) == M_RNG) {
						if (table->__collate_load_error ?
						    CHAR(c) <= CHAR(k) &&
						    CHAR(k) <= CHAR(pat[1]) :
						    __wcollate_range_cmp(CHAR(c),
						    CHAR(k)) <= 0 &&
						    __wcollate_range_cmp(CHAR(k),
						    CHAR(pat[1])) <= 0)
							ok = 1;
						pat += 2;
					} else if (c == k)
						ok = 1;
				if (ok == negate_range)
					goto fail;
				break;
			default:
				if (*name++ != c)
					goto fail;
				break;
			}
		}
		if (*name == EOS)
			return (1);

	fail:
		if (nextn == NULL)
			break;
		pat = nextp;
		name = nextn;
	}
	return (0);
}