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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int WORDBUF_SIZE ; 
 char* emalloc (int) ; 
 char** erealloc (char**,unsigned int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 size_t strcspn (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static unsigned
read_words (const char *filename, char ***ret_w)
{
    unsigned n, alloc;
    FILE *f;
    char buf[256];
    char **w = NULL;
    char *wbuf = NULL, *wptr = NULL, *wend = NULL;

    f = fopen (filename, "r");
    if (f == NULL)
	err (1, "cannot open %s", filename);
    alloc = n = 0;
    while (fgets (buf, sizeof(buf), f) != NULL) {
	size_t len;

	buf[strcspn(buf, "\r\n")] = '\0';
	if (n >= alloc) {
	    alloc = max(alloc + 16, alloc * 2);
	    w = erealloc (w, alloc * sizeof(char **));
	}
	len = strlen(buf);
	if (wptr + len + 1 >= wend) {
	    wptr = wbuf = emalloc (WORDBUF_SIZE);
	    wend = wbuf + WORDBUF_SIZE;
	}
	memmove (wptr, buf, len + 1);
	w[n++] = wptr;
	wptr += len + 1;
    }
    if (n == 0)
	errx(1, "%s is an empty file, no words to try", filename);
    *ret_w = w;
    fclose(f);
    return n;
}