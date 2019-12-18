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
struct tac_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  generr (struct tac_handle*,char*) ; 
 void* malloc (size_t) ; 

__attribute__((used)) static void *
xmalloc(struct tac_handle *h, size_t size)
{
	void *r;

	if ((r = malloc(size)) == NULL)
		generr(h, "Out of memory");
	return r;
}