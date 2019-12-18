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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_BUF ; 
 size_t MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  err (int,char*) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int fseeko (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
consume(FILE *fp, off_t len, char *buf, int reg)
{
	size_t l;

	if (reg) {
		if (fseeko(fp, len, SEEK_CUR) == -1)
			err(1, NULL);
	}
	else {
		while (len > 0) {
			l = MIN(DEF_BUF, len);
			if (fread(buf, sizeof(char), l, fp) != l)
				err(1, "cannot read buffer");
			len -= l;
		}
	}
}