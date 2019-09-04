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
typedef  int /*<<< orphan*/  s ;
typedef  unsigned int index_type ;
typedef  char Py_UCS4 ;

/* Variables and functions */
 unsigned int snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static inline bool
write_sgr(const char *val, Py_UCS4 *buf, index_type buflen, index_type *i) {
    static char s[128];
    unsigned int num = snprintf(s, sizeof(s), "\x1b[%sm", val);
    if (buflen - (*i) < num + 3) return false;
    for(unsigned int si=0; si < num; si++) buf[(*i)++] = s[si];
    return true;
}