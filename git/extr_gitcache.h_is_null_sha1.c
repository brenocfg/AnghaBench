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
 int hasheq (unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_sha1 ; 

__attribute__((used)) static inline int is_null_sha1(const unsigned char *sha1)
{
	return hasheq(sha1, null_sha1);
}