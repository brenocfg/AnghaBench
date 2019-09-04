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
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  FALSE ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void write_item(const char *what, LPCWSTR wbuf, int wlen)
{
	char *buf;

	if (!wbuf || !wlen) {
		printf("%s=\n", what);
		return;
	}

	int len = WideCharToMultiByte(CP_UTF8, 0, wbuf, wlen, NULL, 0, NULL,
	    FALSE);
	buf = xmalloc(len);

	if (!WideCharToMultiByte(CP_UTF8, 0, wbuf, wlen, buf, len, NULL, FALSE))
		die("WideCharToMultiByte failed!");

	printf("%s=", what);
	fwrite(buf, 1, len, stdout);
	putchar('\n');
	free(buf);
}