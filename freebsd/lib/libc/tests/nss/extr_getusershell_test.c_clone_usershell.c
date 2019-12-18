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
struct usershell {int /*<<< orphan*/ * path; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clone_usershell(struct usershell *dest, struct usershell const *src)
{
	assert(dest != NULL);
	assert(src != NULL);

	if (src->path != NULL) {
		dest->path = strdup(src->path);
		assert(dest->path != NULL);
	}
}