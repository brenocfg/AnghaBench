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
 char* BRK_END_XML_TOKEN_CHARS (char const*) ; 
 char const NUL ; 

__attribute__((used)) inline static char const *
skip_unkn(char const * txt)
{
    txt = BRK_END_XML_TOKEN_CHARS(txt);
    return (*txt == NUL) ? NULL : txt;
}