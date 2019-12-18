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
 int /*<<< orphan*/  add_char (char*,size_t,size_t,char const) ; 
 char const* quotable_chars ; 
 char const* replace_chars ; 
 char* strchr (char const*,char const) ; 

__attribute__((used)) static size_t
quote_string(const char *s, char *out, size_t idx, size_t len, int display)
{
    const char *p, *q;
    for(p = s; *p && idx < len; p++){
	q = strchr(quotable_chars, *p);
	if (q && display) {
	    add_char(out, idx, len, replace_chars[q - quotable_chars]);
	} else if (q) {
	    add_char(out, idx, len, '\\');
	    add_char(out, idx, len, replace_chars[q - quotable_chars]);
	}else
	    add_char(out, idx, len, *p);
    }
    if(idx < len)
	out[idx] = '\0';
    return idx;
}