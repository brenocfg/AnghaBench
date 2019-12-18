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

/* Variables and functions */
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  urandom_fd ; 

__attribute__((used)) static int _urandom(void *ctx, unsigned char *out, size_t len)
{
	read(urandom_fd, out, len);
	return 0;
}