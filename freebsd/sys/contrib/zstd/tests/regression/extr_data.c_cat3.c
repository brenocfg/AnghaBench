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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ malloc (size_t const) ; 
 int /*<<< orphan*/  strcpy (char* const,char const*) ; 
 size_t const strlen (char* const) ; 

__attribute__((used)) static char* cat3(char const* str1, char const* str2, char const* str3) {
    size_t const size1 = strlen(str1);
    size_t const size2 = strlen(str2);
    size_t const size3 = str3 == NULL ? 0 : strlen(str3);
    size_t const size = size1 + size2 + size3 + 1;
    char* const dst = (char*)malloc(size);
    if (dst == NULL)
        return NULL;
    strcpy(dst, str1);
    strcpy(dst + size1, str2);
    if (str3 != NULL)
        strcpy(dst + size1 + size2, str3);
    assert(strlen(dst) == size1 + size2 + size3);
    return dst;
}