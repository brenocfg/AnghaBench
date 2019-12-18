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
 char* calloc (size_t,int) ; 
 int /*<<< orphan*/  encodeUTF8 (char*,char const) ; 

__attribute__((used)) static char* convertLatin1toUTF8(const char* source)
{
    size_t size = 1;
    const char* sp;

    for (sp = source;  *sp;  sp++)
        size += (*sp & 0x80) ? 2 : 1;

    char* target = calloc(size, 1);
    char* tp = target;

    for (sp = source;  *sp;  sp++)
        tp += encodeUTF8(tp, *sp);

    return target;
}