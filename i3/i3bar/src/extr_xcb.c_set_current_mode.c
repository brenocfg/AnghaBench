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
struct mode {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  I3STRING_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  activated_mode ; 
 struct mode binding ; 

void set_current_mode(struct mode *current) {
    I3STRING_FREE(binding.name);
    binding = *current;
    activated_mode = binding.name != NULL;
}