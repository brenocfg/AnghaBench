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
struct vector_type_qualifier {int /*<<< orphan*/  ext_name; int /*<<< orphan*/  q_container; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vector_str_dest (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vector_type_qualifier_dest(struct vector_type_qualifier *v)
{

	if (v == NULL)
		return;

	free(v->q_container);
	vector_str_dest(&v->ext_name);
}