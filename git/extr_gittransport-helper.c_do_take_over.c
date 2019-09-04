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
struct transport {scalar_t__ data; } ;
struct helper_data {int /*<<< orphan*/  out; int /*<<< orphan*/  helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct helper_data*) ; 
 int /*<<< orphan*/  transport_take_over (struct transport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_take_over(struct transport *transport)
{
	struct helper_data *data;
	data = (struct helper_data *)transport->data;
	transport_take_over(transport, data->helper);
	fclose(data->out);
	free(data);
}