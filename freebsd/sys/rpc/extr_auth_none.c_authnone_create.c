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
struct authnone_private {int /*<<< orphan*/  no_client; } ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct authnone_private authnone_private ; 

AUTH *
authnone_create()
{
	struct authnone_private *ap = &authnone_private;

	return (&ap->no_client);
}