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
 char* makebuf (size_t,int) ; 
 scalar_t__ memcmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 char* stpncpy (char*,char*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
test_stpncpy(const char *s)
{
	char *src, *dst;
	size_t size, len, bufsize, x;
	int i, j;

	size = strlen(s) + 1;
	for (i = 0; i <= 1; i++) {
		for (j = 0; j <= 1; j++) {
			for (bufsize = 0; bufsize <= size + 10; bufsize++) {
				src = makebuf(size, i);
				memcpy(src, s, size);
				dst = makebuf(bufsize, j);
				memset(dst, 'X', bufsize);
				len = (bufsize < size) ? bufsize : size - 1;
				assert(stpncpy(dst, src, bufsize) == dst+len);
				assert(memcmp(src, dst, len) == 0);
				for (x = len; x < bufsize; x++)
					assert(dst[x] == '\0');
			}
		}
	}
}