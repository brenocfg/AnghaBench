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
typedef  int /*<<< orphan*/  sha1nfo ;

/* Variables and functions */
 int /*<<< orphan*/  sha1_write1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sha1_write(sha1nfo *s, const char *data, size_t len)
{
	while (len--) sha1_write1(s, (uint8_t)*data++);
}