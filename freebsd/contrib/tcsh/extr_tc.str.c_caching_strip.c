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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strip (char*) ; 
 int strlen (char const*) ; 
 char* xrealloc (char*,size_t) ; 

char *
caching_strip(const char *s)
{
    static char *buf = NULL;
    static size_t buf_size = 0;
    size_t size;

    if (s == NULL)
      return NULL;
    size = strlen(s) + 1;
    if (buf_size < size) {
	buf = xrealloc(buf, size);
	buf_size = size;
    }
    memcpy(buf, s, size);
    strip(buf);
    return buf;
}