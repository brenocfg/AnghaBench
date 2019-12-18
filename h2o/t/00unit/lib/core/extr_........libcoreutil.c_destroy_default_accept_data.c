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
struct st_h2o_accept_data_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_accept_data (struct st_h2o_accept_data_t*) ; 

__attribute__((used)) static void destroy_default_accept_data(struct st_h2o_accept_data_t *_accept_data)
{
    destroy_accept_data(_accept_data);
}