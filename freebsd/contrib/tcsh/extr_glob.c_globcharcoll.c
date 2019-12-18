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
typedef  char wchar_t ;
typedef  int __Char ;

/* Variables and functions */
 scalar_t__ islower (int) ; 
 scalar_t__ isupper (int) ; 
 scalar_t__ iswlower (int) ; 
 scalar_t__ iswupper (int) ; 
 int strcoll (char*,char*) ; 
 int tolower (int) ; 
 int towlower (int) ; 
 int wcscoll (char*,char*) ; 

int
globcharcoll(__Char c1, __Char c2, int cs)
{
#if defined(NLS) && defined(LC_COLLATE) && defined(HAVE_STRCOLL)
# if defined(WIDE_STRINGS)
    wchar_t s1[2], s2[2];

    if (c1 == c2)
	return (0);
    if (cs) {
	c1 = towlower(c1);
	c2 = towlower(c2);
    } else {
#ifndef __FreeBSD__
	/* This should not be here, but I'll rather leave it in than engage in
	   a LC_COLLATE flamewar about a shell I don't use... */
	if (iswlower(c1) && iswupper(c2))
	    return (1);
	if (iswupper(c1) && iswlower(c2))
	    return (-1);
#endif
    }
    s1[0] = c1;
    s2[0] = c2;
    s1[1] = s2[1] = '\0';
    return wcscoll(s1, s2);
# else /* not WIDE_STRINGS */
    char s1[2], s2[2];

    if (c1 == c2)
	return (0);
    /*
     * From kevin lyda <kevin@suberic.net>:
     * strcoll does not guarantee case sorting, so we pre-process now:
     */
    if (cs) {
	c1 = islower(c1) ? c1 : tolower(c1);
	c2 = islower(c2) ? c2 : tolower(c2);
    } else {
	if (islower(c1) && isupper(c2))
	    return (1);
	if (isupper(c1) && islower(c2))
	    return (-1);
    }
    s1[0] = c1;
    s2[0] = c2;
    s1[1] = s2[1] = '\0';
    return strcoll(s1, s2);
# endif
#else
    return (c1 - c2);
#endif
}