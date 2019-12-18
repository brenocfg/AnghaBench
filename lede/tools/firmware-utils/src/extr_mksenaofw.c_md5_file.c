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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  MD5_CTX ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUF_SIZE ; 
 int /*<<< orphan*/  MD5_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,char**,size_t) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (char**,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int md5_file(const char *filename, uint8_t *dst)
{
	FILE *fp_src;
	MD5_CTX ctx;
	char buf[BUF_SIZE];
	size_t bytes_read;

	MD5_Init(&ctx);

	fp_src = fopen(filename, "r+b");
	if (!fp_src) {
		return -1;
	}
	while (!feof(fp_src)) {
		bytes_read = fread(&buf, 1, BUF_SIZE, fp_src);
		MD5_Update(&ctx, &buf, bytes_read);
	}
	fclose(fp_src);

	MD5_Final(dst, &ctx);

	return 0;
}