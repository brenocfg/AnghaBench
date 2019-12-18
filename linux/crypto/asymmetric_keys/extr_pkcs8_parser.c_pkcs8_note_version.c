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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

int pkcs8_note_version(void *context, size_t hdrlen,
		       unsigned char tag,
		       const void *value, size_t vlen)
{
	if (vlen != 1 || ((const u8 *)value)[0] != 0) {
		pr_warn("Unsupported PKCS#8 version\n");
		return -EBADMSG;
	}
	return 0;
}