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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  ERANGE ; 
 int el_wgetc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int wctob (int /*<<< orphan*/ ) ; 

int
el_getc(EditLine *el, char *cp)
{
	int num_read;
	wchar_t wc = 0;

	num_read = el_wgetc(el, &wc);
	*cp = '\0';
	if (num_read <= 0)
		return num_read;
	num_read = wctob(wc);
	if (num_read == EOF) {
		errno = ERANGE;
		return -1;
	} else {
		*cp = (char)num_read;
		return 1;
	}
}