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
struct st_h2o_accept_data_t {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct st_h2o_accept_data_t*) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_accept_data(struct st_h2o_accept_data_t *data)
{
    h2o_timer_unlink(&data->timeout);
    free(data);
}