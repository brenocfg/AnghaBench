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
struct outputs_json_params {int /*<<< orphan*/  cur_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int outputs_null_cb(void *params_) {
    struct outputs_json_params *params = (struct outputs_json_params *)params_;

    FREE(params->cur_key);

    return 1;
}