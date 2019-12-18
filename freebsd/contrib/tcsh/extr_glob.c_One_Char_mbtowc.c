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
typedef  int __Char ;
typedef  int Char ;

/* Variables and functions */
 int const CHAR ; 
 int /*<<< orphan*/  LCHAR (int /*<<< orphan*/ ) ; 
 int MB_LEN_MAX ; 
 size_t one_mbtowc (int*,char*,size_t) ; 

__attribute__((used)) static size_t
One_Char_mbtowc(__Char *pwc, const Char *s, size_t n)
{
#ifdef WIDE_STRINGS
    char buf[MB_LEN_MAX], *p;

    if (n > MB_LEN_MAX)
	n = MB_LEN_MAX;
    p = buf;
    while (p < buf + n && (*p++ = LCHAR(*s++)) != 0)
	;
    return one_mbtowc(pwc, buf, n);
#else
    *pwc = *s & CHAR;
    return 1;
#endif
}