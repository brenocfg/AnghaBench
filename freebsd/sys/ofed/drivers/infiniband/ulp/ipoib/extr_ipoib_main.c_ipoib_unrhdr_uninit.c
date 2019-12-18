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
struct unrhdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_unrhdr (struct unrhdr*) ; 
 struct unrhdr* ipoib_unrhdr ; 

__attribute__((used)) static void
ipoib_unrhdr_uninit(void *arg)
{

	if (ipoib_unrhdr != NULL) {
		struct unrhdr *hdr;

		hdr = ipoib_unrhdr;
		ipoib_unrhdr = NULL;

		delete_unrhdr(hdr);
	}
}