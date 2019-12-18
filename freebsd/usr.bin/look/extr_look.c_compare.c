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
typedef  unsigned char wchar_t ;

/* Variables and functions */
 int EQUAL ; 
 int GREATER ; 
 int LESS ; 
 scalar_t__ dflag ; 
 scalar_t__ fflag ; 
 int /*<<< orphan*/  iswalnum (unsigned char) ; 
 size_t mbrtowc (unsigned char*,unsigned char*,int,int /*<<< orphan*/ *) ; 
 unsigned char towlower (unsigned char) ; 

__attribute__((used)) static int
compare(wchar_t *s1, unsigned char *s2, unsigned char *back)
{
	wchar_t ch1, ch2;
	size_t len2;

	for (; *s1 && s2 < back && *s2 != '\n'; ++s1, s2 += len2) {
		ch1 = *s1;
		len2 = mbrtowc(&ch2, s2, back - s2, NULL);
		if (len2 == (size_t)-1 || len2 == (size_t)-2) {
			ch2 = *s2;
			len2 = 1;
		}
		if (fflag)
			ch2 = towlower(ch2);
		if (dflag && !iswalnum(ch2)) {
			/* Ignore character in comparison. */
			--s1;
			continue;
		}
		if (ch1 != ch2)
			return (ch1 < ch2 ? LESS : GREATER);
	}
	return (*s1 ? GREATER : EQUAL);
}