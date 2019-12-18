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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int buffer_write (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ data_prot ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  out_buffer ; 
 scalar_t__ prot_clear ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 
 int vfprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

int
sec_vfprintf2(FILE *f, const char *fmt, va_list ap)
{
    char *buf;
    int ret;
    if(data_prot == prot_clear)
	return vfprintf(f, fmt, ap);
    else {
	int len;
	len = vasprintf(&buf, fmt, ap);
	if (len == -1)
	    return len;
	ret = buffer_write(&out_buffer, buf, len);
	free(buf);
	return ret;
    }
}