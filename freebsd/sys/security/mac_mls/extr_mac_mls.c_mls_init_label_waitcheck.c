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
struct label {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * SLOT (struct label*) ; 
 int /*<<< orphan*/  SLOT_SET (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mls_alloc (int) ; 

__attribute__((used)) static int
mls_init_label_waitcheck(struct label *label, int flag)
{

	SLOT_SET(label, mls_alloc(flag));
	if (SLOT(label) == NULL)
		return (ENOMEM);

	return (0);
}