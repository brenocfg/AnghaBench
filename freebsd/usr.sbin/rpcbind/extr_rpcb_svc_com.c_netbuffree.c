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
struct netbuf {struct netbuf* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct netbuf*) ; 

__attribute__((used)) static void
netbuffree(struct netbuf *ap)
{

	if (ap == NULL)
		return;
	free(ap->buf);
	ap->buf = NULL;
	free(ap);
}