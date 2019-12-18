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
struct bridge_ifs {int dummy; } ;
struct bridge_if {int dummy; } ;

/* Variables and functions */
 struct bridge_if* TAILQ_FIRST (struct bridge_ifs*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct bridge_ifs*,struct bridge_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_if ; 
 int /*<<< orphan*/  free (struct bridge_if*) ; 

__attribute__((used)) static void
bridge_ifs_free(struct bridge_ifs *headp)
{
	struct bridge_if *b;

	while ((b = TAILQ_FIRST(headp)) != NULL) {
		TAILQ_REMOVE(headp, b, b_if);
		free(b);
	}
}