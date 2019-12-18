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

/* Variables and functions */
 scalar_t__ paginate_lpp ; 
 scalar_t__ paginate_pos ; 
 int paginate_skipping ; 
 int paginating ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 int udbg_write (char const*,int) ; 
 int xmon_readchar () ; 

__attribute__((used)) static int xmon_write(const char *ptr, int nb)
{
	int rv = 0;
	const char *p = ptr, *q;
	const char msg[] = "[Hit a key (a:all, q:truncate, any:next page)]";

	if (nb <= 0)
		return rv;

	if (paginating && paginate_skipping)
		return nb;

	if (paginate_lpp) {
		while (paginating && (q = strchr(p, '\n'))) {
			rv += udbg_write(p, q - p + 1);
			p = q + 1;
			paginate_pos++;

			if (paginate_pos >= paginate_lpp) {
				udbg_write(msg, strlen(msg));

				switch (xmon_readchar()) {
				case 'a':
					paginating = false;
					break;
				case 'q':
					paginate_skipping = true;
					break;
				default:
					/* nothing */
					break;
				}

				paginate_pos = 0;
				udbg_write("\r\n", 2);

				if (paginate_skipping)
					return nb;
			}
		}
	}

	return rv + udbg_write(p, nb - (p - ptr));
}