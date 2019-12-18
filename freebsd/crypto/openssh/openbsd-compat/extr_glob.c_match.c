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
struct TYPE_2__ {int /*<<< orphan*/  (* isctype ) (int) ;} ;
typedef  int Char ;

/* Variables and functions */
 int EOS ; 
 int GLOB_NOSPACE ; 
#define  M_ALL 130 
 int M_CLASS ; 
 int M_END ; 
 int M_MASK ; 
 int M_NOT ; 
#define  M_ONE 129 
 int M_RNG ; 
#define  M_SET 128 
 int NCCLASSES ; 
 TYPE_1__* cclasses ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static int
match(Char *name, Char *pat, Char *patend, int recur)
{
	int ok, negate_range;
	Char c, k;

	if (recur-- == 0)
		return(GLOB_NOSPACE);

	while (pat < patend) {
		c = *pat++;
		switch (c & M_MASK) {
		case M_ALL:
			while (pat < patend && (*pat & M_MASK) == M_ALL)
				pat++;	/* eat consecutive '*' */
			if (pat == patend)
				return(1);
			do {
			    if (match(name, pat, patend, recur))
				    return(1);
			} while (*name++ != EOS);
			return(0);
		case M_ONE:
			if (*name++ == EOS)
				return(0);
			break;
		case M_SET:
			ok = 0;
			if ((k = *name++) == EOS)
				return(0);
			if ((negate_range = ((*pat & M_MASK) == M_NOT)) != EOS)
				++pat;
			while (((c = *pat++) & M_MASK) != M_END) {
				if ((c & M_MASK) == M_CLASS) {
					Char idx = *pat & M_MASK;
					if (idx < NCCLASSES &&
					    cclasses[idx].isctype(k))
						ok = 1;
					++pat;
				}
				if ((*pat & M_MASK) == M_RNG) {
					if (c <= k && k <= pat[1])
						ok = 1;
					pat += 2;
				} else if (c == k)
					ok = 1;
			}
			if (ok == negate_range)
				return(0);
			break;
		default:
			if (*name++ != c)
				return(0);
			break;
		}
	}
	return(*name == EOS);
}