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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (unsigned char const*,size_t,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ucl_file_append_len (const unsigned char *str, size_t len, void *ud)
{
	FILE *fp = ud;

	fwrite (str, len, 1, fp);

	return 0;
}