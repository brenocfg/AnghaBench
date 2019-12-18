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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  u32 ;
struct uimage_header {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int FW_EDIMAX_OFFSET ; 
 scalar_t__ FW_MAGIC_EDIMAX ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  uimage_verify_default (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ssize_t uimage_find_edimax(u_char *buf, size_t len)
{
	u32 *magic;

	if (len < FW_EDIMAX_OFFSET + sizeof(struct uimage_header)) {
		pr_err("Buffer too small for checking Edimax header\n");
		return -ENOSPC;
	}

	magic = (u32 *)buf;
	if (be32_to_cpu(*magic) != FW_MAGIC_EDIMAX)
		return -EINVAL;

	if (!uimage_verify_default(buf + FW_EDIMAX_OFFSET, len))
		return FW_EDIMAX_OFFSET;

	return -EINVAL;
}