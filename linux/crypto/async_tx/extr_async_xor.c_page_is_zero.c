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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memchr_inv (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ page_address (struct page*) ; 

__attribute__((used)) static int page_is_zero(struct page *p, unsigned int offset, size_t len)
{
	return !memchr_inv(page_address(p) + offset, 0, len);
}