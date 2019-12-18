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
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

__attribute__((used)) static void
MD5_Update(MD5_CTX *c, const unsigned char *data, size_t len)
{
	MD5Update(c, data, len);
}