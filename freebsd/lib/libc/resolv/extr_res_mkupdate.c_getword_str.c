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
typedef  void* u_char ;

/* Variables and functions */
 scalar_t__ isspace (int) ; 

__attribute__((used)) static int
getword_str(char *buf, int size, u_char **startpp, u_char *endp) {
        char *cp;
        int c;
 
        for (cp = buf; *startpp <= endp; ) {
                c = **startpp;
                if (isspace(c) || c == '\0') {
                        if (cp != buf) /*%< trailing whitespace */
                                break;
                        else { /*%< leading whitespace */
                                (*startpp)++;
                                continue;
                        }
                }
                (*startpp)++;
                if (cp >= buf+size-1)
                        break;
                *cp++ = (u_char)c;
        }
        *cp = '\0';
        return (cp != buf);
}