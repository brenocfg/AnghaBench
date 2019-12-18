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
 int BIO_dump_indent_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int,int) ; 
 int /*<<< orphan*/  write_fp ; 

int BIO_dump_indent_fp(FILE *fp, const char *s, int len, int indent)
{
    return BIO_dump_indent_cb(write_fp, fp, s, len, indent);
}