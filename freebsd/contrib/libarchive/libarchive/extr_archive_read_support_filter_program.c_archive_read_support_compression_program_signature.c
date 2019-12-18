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
struct archive {int dummy; } ;

/* Variables and functions */
 int archive_read_support_filter_program_signature (struct archive*,char const*,void const*,size_t) ; 

int
archive_read_support_compression_program_signature(struct archive *a,
    const char *cmd, const void *signature, size_t signature_len)
{
	return archive_read_support_filter_program_signature(a,
	    cmd, signature, signature_len);
}