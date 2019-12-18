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
typedef  int uintmax_t ;
typedef  size_t off_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 size_t fwrite (char*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
head_bytes(FILE *fp, off_t cnt)
{
	char buf[4096];
	size_t readlen;

	while (cnt) {
		if ((uintmax_t)cnt < sizeof(buf))
			readlen = cnt;
		else
			readlen = sizeof(buf);
		readlen = fread(buf, sizeof(char), readlen, fp);
		if (readlen == 0)
			break;
		if (fwrite(buf, sizeof(char), readlen, stdout) != readlen)
			err(1, "stdout");
		cnt -= readlen;
	}
}