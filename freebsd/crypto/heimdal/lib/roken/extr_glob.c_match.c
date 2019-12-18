#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int Char ;

/* Variables and functions */
 int CHAR_EOS ; 
#define  M_ALL 130 
 int M_END ; 
 int M_MASK ; 
 int M_NOT ; 
#define  M_ONE 129 
 int M_RNG ; 
#define  M_SET 128 

__attribute__((used)) static int
match(Char *name, Char *pat, Char *patend)
{
	int ok, negate_range;
	Char c, k;

	while (pat < patend) {
		c = *pat++;
		switch (c & M_MASK) {
		case M_ALL:
			if (pat == patend)
				return(1);
			do
			    if (match(name, pat, patend))
				    return(1);
			while (*name++ != CHAR_EOS);
			return(0);
		case M_ONE:
			if (*name++ == CHAR_EOS)
				return(0);
			break;
		case M_SET:
			ok = 0;
			if ((k = *name++) == CHAR_EOS)
				return(0);
			if ((negate_range = ((*pat & M_MASK) == M_NOT)) != CHAR_EOS)
				++pat;
			while (((c = *pat++) & M_MASK) != M_END)
				if ((*pat & M_MASK) == M_RNG) {
					if (c <= k && k <= pat[1])
						ok = 1;
					pat += 2;
				} else if (c == k)
					ok = 1;
			if (ok == negate_range)
				return(0);
			break;
		default:
			if (*name++ != c)
				return(0);
			break;
		}
	}
	return(*name == CHAR_EOS);
}