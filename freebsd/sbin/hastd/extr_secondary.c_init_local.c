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
struct hast_resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_NOINPUT ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int metadata_read (struct hast_resource*,int) ; 

__attribute__((used)) static void
init_local(struct hast_resource *res)
{

	if (metadata_read(res, true) == -1)
		exit(EX_NOINPUT);
}