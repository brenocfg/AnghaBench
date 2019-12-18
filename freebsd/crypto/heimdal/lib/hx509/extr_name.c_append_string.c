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
 int /*<<< orphan*/  Q_RFC2253 ; 
 int /*<<< orphan*/  _hx509_abort (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* quote_string (char const*,size_t,int /*<<< orphan*/ ,size_t*) ; 
 char* realloc (char*,size_t) ; 
 char* rk_UNCONST (char const*) ; 

__attribute__((used)) static int
append_string(char **str, size_t *total_len, const char *ss,
	      size_t len, int quote)
{
    char *s, *qs;

    if (quote)
	qs = quote_string(ss, len, Q_RFC2253, &len);
    else
	qs = rk_UNCONST(ss);

    s = realloc(*str, len + *total_len + 1);
    if (s == NULL)
	_hx509_abort("allocation failure"); /* XXX */
    memcpy(s + *total_len, qs, len);
    if (qs != ss)
	free(qs);
    s[*total_len + len] = '\0';
    *str = s;
    *total_len += len;
    return 0;
}