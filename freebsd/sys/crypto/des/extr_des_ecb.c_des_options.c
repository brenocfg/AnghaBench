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
typedef  int /*<<< orphan*/  DES_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*,char const*,char const*) ; 

char *des_options(void)
        {
        static int init=1;
        static char buf[32];

        if (init)
                {
                const char *ptr,*unroll,*risc,*size;

#ifdef DES_PTR
                ptr="ptr";
#else
                ptr="idx";
#endif
#if defined(DES_RISC1) || defined(DES_RISC2)
#ifdef DES_RISC1
                risc="risc1";
#endif
#ifdef DES_RISC2
                risc="risc2";
#endif
#else
                risc="cisc";
#endif
#ifdef DES_UNROLL
                unroll="16";
#else
                unroll="4";
#endif
                if (sizeof(DES_LONG) != sizeof(long))
                        size="int";
                else
                        size="long";
                sprintf(buf,"des(%s,%s,%s,%s)",ptr,risc,unroll,size);
                init=0;
                }
        return(buf);
}