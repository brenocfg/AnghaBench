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

/* Variables and functions */
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int strcoll (char const*,char const*) ; 
 int /*<<< orphan*/ * towcs (char const*) ; 
 int wcscoll (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mbscoll(const char *s1, const char *s2)
{
	wchar_t *w1, *w2;
	int ret;

	if (MB_CUR_MAX == 1)
		return (strcoll(s1, s2));
	if ((w1 = towcs(s1)) == NULL || (w2 = towcs(s2)) == NULL)
		err(1, NULL);	/* XXX */
	ret = wcscoll(w1, w2);
	free(w1);
	free(w2);
	return (ret);
}