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
struct putchar_arg {int* buf; int n_next; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  HYPERVISOR_console_write (char*,int) ; 

__attribute__((used)) static void
putchar(int c, void *arg)
{
	struct putchar_arg *pca;

	pca = (struct putchar_arg *)arg;

	if (pca->buf == NULL) {
		/*
		 * We have no buffer, output directly to the
		 * console char by char.
		 */
		HYPERVISOR_console_write((char *)&c, 1);
	} else {
		pca->buf[pca->n_next++] = c;
		if ((pca->size == pca->n_next) || (c = '\0')) {
			/* Flush the buffer */
			HYPERVISOR_console_write(pca->buf, pca->n_next);
			pca->n_next = 0;
		}
	}
}