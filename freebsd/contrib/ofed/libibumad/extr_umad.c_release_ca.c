#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numports; int /*<<< orphan*/ ** ports; } ;
typedef  TYPE_1__ umad_ca_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_port (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int release_ca(umad_ca_t * ca)
{
	int i;

	for (i = 0; i <= ca->numports; i++) {
		if (!ca->ports[i])
			continue;
		release_port(ca->ports[i]);
		free(ca->ports[i]);
		ca->ports[i] = NULL;
	}
	return 0;
}