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
struct transport {struct helper_data* data; } ;
struct helper_data {int /*<<< orphan*/  rs; } ;

/* Variables and functions */
 int disconnect_helper (struct transport*) ; 
 int /*<<< orphan*/  free (struct helper_data*) ; 
 int /*<<< orphan*/  refspec_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int release_helper(struct transport *transport)
{
	int res = 0;
	struct helper_data *data = transport->data;
	refspec_clear(&data->rs);
	res = disconnect_helper(transport);
	free(transport->data);
	return res;
}