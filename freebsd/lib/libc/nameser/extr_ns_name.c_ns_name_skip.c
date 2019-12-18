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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
#define  NS_CMPRSFLGS 129 
#define  NS_TYPE_ELT 128 
 int /*<<< orphan*/  errno ; 
 int labellen (int /*<<< orphan*/  const*) ; 

int
ns_name_skip(const u_char **ptrptr, const u_char *eom)
{
	const u_char *cp;
	u_int n;
	int l = 0;

	cp = *ptrptr;
	while (cp < eom && (n = *cp++) != 0) {
		/* Check for indirection. */
		switch (n & NS_CMPRSFLGS) {
		case 0:			/*%< normal case, n == len */
			cp += n;
			continue;
		case NS_TYPE_ELT: /*%< EDNS0 extended label */
			if (cp < eom && (l = labellen(cp - 1)) < 0) {
				errno = EMSGSIZE; /*%< XXX */
				return (-1);
			}
			cp += l;
			continue;
		case NS_CMPRSFLGS:	/*%< indirection */
			cp++;
			break;
		default:		/*%< illegal type */
			errno = EMSGSIZE;
			return (-1);
		}
		break;
	}
	if (cp > eom) {
		errno = EMSGSIZE;
		return (-1);
	}
	*ptrptr = cp;
	return (0);
}