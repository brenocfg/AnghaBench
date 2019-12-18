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
struct atmel_sha_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA_HW_VERSION ; 
 int atmel_sha_read (struct atmel_sha_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int atmel_sha_get_version(struct atmel_sha_dev *dd)
{
	return atmel_sha_read(dd, SHA_HW_VERSION) & 0x00000fff;
}