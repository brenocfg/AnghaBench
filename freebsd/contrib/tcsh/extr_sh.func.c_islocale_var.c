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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
#define  STRLANG 135 
#define  STRLC_ALL 134 
#define  STRLC_COLLATE 133 
#define  STRLC_CTYPE 132 
#define  STRLC_MESSAGES 131 
#define  STRLC_MONETARY 130 
#define  STRLC_NUMERIC 129 
#define  STRLC_TIME 128 
 scalar_t__ eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
islocale_var(Char *var)
{
    static Char *locale_vars[] = {
	STRLANG,	STRLC_ALL, 	STRLC_CTYPE,	STRLC_NUMERIC,
	STRLC_TIME,	STRLC_COLLATE,	STRLC_MESSAGES,	STRLC_MONETARY, 0
    };
    Char **v;

    for (v = locale_vars; *v; ++v)
	if (eq(var, *v))
	    return 1;
    return 0;
}