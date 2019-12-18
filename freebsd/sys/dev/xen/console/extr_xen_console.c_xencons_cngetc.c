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
struct consdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  main_cons ; 
 int xencons_getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xencons_rx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xencons_cngetc(struct consdev *dev)
{

	xencons_rx(&main_cons);

	return (xencons_getc(&main_cons));
}